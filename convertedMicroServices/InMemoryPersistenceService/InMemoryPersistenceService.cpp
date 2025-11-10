#include "InMemoryPersistenceService.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

InMemoryPersistenceService::InMemoryPersistenceService() : posts() {}

void InMemoryPersistenceService::SavePost(const Post& post) {
    this->posts.push_back(post);
}

std::vector<Post> InMemoryPersistenceService::GetAllPosts() const {
    return this->posts;
}

std::vector<Post> InMemoryPersistenceService::GetPostsByUserId(int64_t user_id) const {
    std::vector<Post> result;
    for (const auto& post : this->posts) {
        if (post.getCreator().user_id == user_id) {
            result.push_back(post);
        }
    }
    return result;
}

EMSCRIPTEN_BINDINGS(in_memory_persistence_module) {
    class_<InMemoryPersistenceService>("InMemoryPersistenceService")
        .constructor<>()
        .function("SavePost", &InMemoryPersistenceService::SavePost)
        .function("GetAllPosts", &InMemoryPersistenceService::GetAllPosts)
        .function("GetPostsByUserId", &InMemoryPersistenceService::GetPostsByUserId)
    ;
    
    register_vector<Post>("PostList");
}