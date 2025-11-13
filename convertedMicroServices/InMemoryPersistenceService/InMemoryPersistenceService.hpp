#pragma once

#include "../Types/Post/Post.hpp"
#include <cstdint>
#include <vector>

class InMemoryPersistenceService {
    public:
        InMemoryPersistenceService();
        void SavePost(const Post& post);
        std::vector<Post> GetAllPosts() const;
        std::vector<Post> GetPostsByUserId(int64_t user_id) const;
        void SaveAllInLocalStorage();
        void DeletePost(int64_t post_id);
        Post* GetPostById(int64_t post_id);
    private:
        std::vector<Post> posts;
};
