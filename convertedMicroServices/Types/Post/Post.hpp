#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include "../Creator/Creator.hpp"
#include "../Media/Media.hpp"
#include "../UserMention/UserMention.hpp"
#include "../Url/Url.hpp"
#include "PostType.hpp"

// Use PostType::type defined in PostType.hpp

class Post {
  public:
    Post() noexcept
      : post_id(0), creator(), req_id(0), text(), user_mentions(), media(), urls(), timestamp(0), post_type(PostType::POST) {}

    int64_t getPostId() const;
    void setPostId(int64_t v);

    Creator getCreator() const;
    void setCreator(const Creator &c);

    int64_t getReqId() const;
    void setReqId(int64_t v);

    std::string getText() const;
    void setText(const std::string &t);

    std::vector<UserMention> getUserMentions() const;
    void setUserMentions(const std::vector<UserMention> &ums);

    std::vector<Media> getMedia() const;
    void setMedia(const std::vector<Media> &m);

    std::vector<Url> getUrls() const;
    void setUrls(const std::vector<Url> &u);

    int64_t getTimestamp() const;
    void setTimestamp(int64_t t);

    PostType::type getPostType() const;
    void setPostType(PostType::type pt);

    int64_t post_id;
    Creator creator;
    int64_t req_id;
    std::string text;
    std::vector<UserMention> user_mentions;
    std::vector<Media> media;
    std::vector<Url> urls;
    int64_t timestamp;
    PostType::type post_type;
};
