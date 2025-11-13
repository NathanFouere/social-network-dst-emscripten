import Module from './wasm/convertedMicroServices.js'

var module = await Module();

const uniqueIdHandler = new module.UniqueIdHandler("abc");
const mediaHandler = new module.MediaHandler();
const socialGraphHandler = new module.SocialGraphHandler();
const sessionStorageUserService = new module.SessionStorageUserService();
const userHandler = new module.UserHandler(socialGraphHandler, uniqueIdHandler, sessionStorageUserService);
const postStorageHandler = new module.PostStorageHandler();
const userMentionHandler = new module.UserMentionHandler();
const textHandler = new module.TextHandler(userMentionHandler);
const userTimelineHandler = new module.UserTimelineHandler(postStorageHandler);
const homeTimelineHandler = new module.HomeTimelineHandler(postStorageHandler, socialGraphHandler);
const composePostHandler = new module.ComposePostHandler(userTimelineHandler, userHandler, uniqueIdHandler, mediaHandler, textHandler, homeTimelineHandler, postStorageHandler);

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
  module: module,
}

export default di;
