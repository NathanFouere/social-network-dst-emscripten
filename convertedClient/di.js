import Module from './wasm/convertedMicroServices.js'

var module = await Module();

const uniqueIdHandler = new module.UniqueIdHandler("abc");
const mediaHandler = new module.MediaHandler();
const socialGraphHandler = new module.SocialGraphHandler();
const userHandler = new module.UserHandler(socialGraphHandler, uniqueIdHandler);
const postStorageHandler = new module.PostStorageHandler();
const userMentionHandler = new module.UserMentionHandler();
const urlShortenHandler = new module.UrlShortenHandler();
const textHandler = new module.TextHandler(urlShortenHandler, userMentionHandler);
const userTimelineHandler = new module.UserTimelineHandler(postStorageHandler);
const homeTimelineHandler = new module.HomeTimelineHandler(postStorageHandler, socialGraphHandler);
const composePostHandler = new module.ComposePostHandler(userTimelineHandler, userHandler, uniqueIdHandler, mediaHandler, textHandler, homeTimelineHandler);

const di = {
  uniqueIdHandler: uniqueIdHandler,
  mediaHandler: mediaHandler,
  socialGraphHandler: socialGraphHandler,
  userHandler: userHandler,
  postStorageHandler: postStorageHandler,
  userMentionHandler: userMentionHandler,
  urlShortenHandler: urlShortenHandler,
  textHandler: textHandler,
  userTimelineHandler: userTimelineHandler,
  composePostHandler: composePostHandler,
  homeTimelineHandler: homeTimelineHandler,
  module: module,
}

export default di;
