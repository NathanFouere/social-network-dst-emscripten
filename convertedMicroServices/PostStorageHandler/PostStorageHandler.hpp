#pragma once

#include "../Types/Post/Post.hpp"
#include <cstdint>
#include <vector>

class PostStorageHandler {
    public:
        PostStorageHandler();
        void StorePost(const Post &post);
        Post ReadPost(int64_t post_id);
        std::vector<Post> ReadPosts(const std::vector<int64_t> &post_ids);
};
