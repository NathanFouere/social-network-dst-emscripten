#pragma once

#include "../Types/Post/Post.hpp"
#include <vector>

class InMemoryPersistenceService {
    public:
        InMemoryPersistenceService();
        void SavePost(const Post& post);
        std::vector<Post> GetAllPosts() const;
        std::vector<Post> GetPostsByUserId(int64_t user_id) const;
    private:
        std::vector<Post> posts;
};