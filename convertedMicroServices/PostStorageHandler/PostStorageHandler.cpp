#include "PostStorageHandler.hpp"
#include <cstdint>
#include <emscripten/bind.h>

using namespace emscripten;

PostStorageHandler::PostStorageHandler() {

}

void PostStorageHandler::StorePost(const Post &post) {
    // TODO => implement
    std::cout << "On stocker un post " << post.getPostId() << std::endl;
}

Post ReadPost(int64_t post_id) {
    // TODO => implement
    std::cout << "On demande la lecture d'un post d'id " << post_id << std::endl;

    Post* fakePost = new Post();

    return *fakePost;
}

std::vector<Post> ReadPosts(const std::vector<int64_t> &post_ids) {
    // TODO => implement
    std::cout << "On demande la lecture d'un post d'id " << post_ids.at(0) << std::endl;

    Post* fakePost = new Post();

    std::vector<Post> fakePosts = {*fakePost};
    return fakePosts;
}

EMSCRIPTEN_BINDINGS(post_storage_module) {
    class_<PostStorageHandler>("PostStorageHandler")
        .constructor<>()
        .function("StorePost", &PostStorageHandler::StorePost)
        .function("ReadPost", &ReadPost)
        .function("ReadPosts", &ReadPosts)
    ;
}
