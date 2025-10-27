#pragma once

#include <string>
#include <vector>
#include "PostType.hpp"
#include "../Media/Media.hpp"
#include "../Creator/Creator.hpp"
#include "../UserMention/UserMention.hpp"
#include "../Url/Url.hpp"

class Post {
    public:
        Post()
            : post_id(0),
            text(),
            timestamp(0),
            post_type(static_cast<PostType::type>(0)) {
        }
        void setPostId(int64_t _post_id);
        int64_t getPostId() const;
        void setCreator(const class Creator& _creator);
        class Creator getCreator() const;
        void setText(const std::string& _text);
        std::string getText() const;
        void setUserMentions(const std::vector<class UserMention>& _user_mentions);
        std::vector<class UserMention> getUserMentions() const;
        void setMedia(const std::vector<class Media>& _media);
        std::vector<class Media> getMedia() const;
        void setUrls(const std::vector<class Url>& _urls);
        std::vector<class Url> getUrls() const;
        void setTimestamp(int64_t _timestamp);
        int64_t getTimestamp() const;
        void setPostType(PostType::type _post_type);
        PostType::type getPostType() const;
    private:
        int64_t post_id;
        class Creator creator;
        std::string text;
        std::vector<class UserMention> user_mentions;
        std::vector<class Media> media;
        std::vector<class Url> urls;
        int64_t timestamp;
        PostType::type post_type;
};
