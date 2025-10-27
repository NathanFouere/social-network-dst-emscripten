import Module from './wasm/convertedMicroServices.js'

var module = await Module();

const uniqueIdHandler = new module.UniqueIdHandler("abc");
const mediaHandler = new module.MediaHandler();
const socialGraphHandler = new module.SocialGraphHandler();
const userHandler = new module.UserHandler(socialGraphHandler, uniqueIdHandler);
const postStorageHandler = new module.PostStorageHandler();
const userMentionHandler = new module.UserMentionHandler();

const di = {
  uniqueIdHandler: uniqueIdHandler,
  mediaHandler: mediaHandler,
  socialGraphHandler: socialGraphHandler,
  userHandler: userHandler,
  postStorageHandler: postStorageHandler,
  userMentionHandler: userMentionHandler,
  module: module,
}

export default di;
