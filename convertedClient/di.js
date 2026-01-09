import Module from "./wasm/convertedMicroServices.js";
import ydoc from "./script/yjs.js";

var module = await Module();

// sert à rendre ydoc disponible globalement dans le module emscripten
module.ydoc = ydoc;

// TODO => tout regrouper dans un promise.all
const randomId = Math.random().toString(36).substring(7);
const uniqueIdHandler = await new module.UniqueIdHandler(randomId);
const mediaHandler = await new module.MediaHandler();
const socialGraphHandler = await new module.SocialGraphHandler();
const sessionStorageUserService = await new module.SessionStorageUserService();
const userHandler = await new module.UserHandler(
  socialGraphHandler,
  uniqueIdHandler,
  sessionStorageUserService,
);
const postStorageHandler = await new module.PostStorageHandler();

// Sync Yjs posts with C++ backend
const postsYArray = ydoc.getArray("posts");
postsYArray.observe(() => {
  console.log("Yjs posts update detected, syncing to C++...");
  try {
    const allPosts = postsYArray.toJSON();
    postStorageHandler.SetAllPosts(JSON.stringify(allPosts));
    window.dispatchEvent(new CustomEvent("posts-updated"));
  } catch (e) {
    console.error("Error syncing Yjs posts to C++:", e);
  }
});

const userMentionHandler = await new module.UserMentionHandler();
const textHandler = await new module.TextHandler(userMentionHandler);
const userTimelineHandler = await new module.UserTimelineHandler(
  postStorageHandler,
);
const homeTimelineHandler = await new module.HomeTimelineHandler(
  postStorageHandler,
  socialGraphHandler,
);
const composePostHandler = await new module.ComposePostHandler(
  userTimelineHandler,
  userHandler,
  uniqueIdHandler,
  mediaHandler,
  textHandler,
  homeTimelineHandler,
  postStorageHandler,
);

const di = {
  uniqueIdHandler: uniqueIdHandler,
  mediaHandler: mediaHandler,
  socialGraphHandler: socialGraphHandler,
  userHandler: userHandler,
  postStorageHandler: postStorageHandler,
  userMentionHandler: userMentionHandler,
  textHandler: textHandler,
  userTimelineHandler: userTimelineHandler,
  composePostHandler: composePostHandler,
  homeTimelineHandler: homeTimelineHandler,
  sessionStorageUserService: sessionStorageUserService,
  ydoc: ydoc,
  module: module,
};

export default di;
