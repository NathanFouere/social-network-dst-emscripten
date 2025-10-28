#include "Post.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

int64_t Post::getPostId() const {
    return this->post_id;
}
void Post::setPostId(int64_t _post_id) {
    this->post_id = _post_id;
}

void Post::setCreator(const class Creator& _creator) {
    this->creator = _creator;
}

class Creator Post::getCreator() const {
    return this->creator;
}
void Post::setText(const std::string& _text) {
    this->text = _text;
}

std::string Post::getText() const {
    return this->text;
}

void Post::setUserMentions(const std::vector<class UserMention>& _user_mentions) {
    this->user_mentions = _user_mentions;
}

std::vector<class UserMention> Post::getUserMentions() const {
    return this->user_mentions;
}

void Post::setMedia(const std::vector<class Media>& _media) {
    this->media = _media;
}

std::vector<class Media> Post::getMedia() const {
    return this->media;
}

void Post::setUrls(const std::vector<class Url>& _urls) {
    this->urls = _urls;
}

std::vector<class Url> Post::getUrls() const {
    return this->urls;
}

void Post::setTimestamp(int64_t _timestamp) {
    this->timestamp = _timestamp;
}

int64_t Post::getTimestamp() const {
    return this->timestamp;
}

void Post::setPostType(PostType::type _post_type) {
    this->post_type = _post_type;
}

PostType::type Post::getPostType() const {
    return this->post_type;
}

EMSCRIPTEN_BINDINGS(post_module) {
    enum_<PostType::type>("PostType")
      .value("POST", PostType::POST)
      .value("REPOST", PostType::REPOST)
      .value("REPLY", PostType::REPLY)
      .value("DM", PostType::DM);

    class_<Post>("Post")
        .constructor<>()
        .property("post_id", &Post::getPostId, &Post::setPostId)
        .property("creator", &Post::getCreator, &Post::setCreator)
        .property("text", &Post::getText, &Post::setText)
        .property("user_mentions", &Post::getUserMentions, &Post::setUserMentions)
        .property("media", &Post::getMedia, &Post::setMedia)
        .property("urls", &Post::getUrls, &Post::setUrls)
        .property("timestamp", &Post::getTimestamp, &Post::setTimestamp)
        .property("post_type", &Post::getPostType, &Post::setPostType)
    ;

    register_vector<UserMention>("UserMentionList");
    register_vector<Media>("MediaList");
    register_vector<Url>("UrlList");
    register_vector<Post>("PostList");

    // Register commonly used primitive lists and maps here to avoid duplicates
    register_vector<std::int64_t>("IntList");
    register_vector<std::string>("StringList");
    register_map<std::string, std::string>("StringStringMap");
}
