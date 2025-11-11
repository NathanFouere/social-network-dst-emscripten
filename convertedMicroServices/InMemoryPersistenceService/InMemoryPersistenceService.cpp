#include "InMemoryPersistenceService.hpp"
#include <emscripten/bind.h>
#include <emscripten.h>
#include <nlohmann/json.hpp>

using namespace emscripten;
using nlohmann::json;


// TODO : placer ces méthodes ailleurs
static Creator loadCreatorFromJson(json j) {
    Creator* creator = new Creator();
    creator->setUserId(j["user_id"]);
    creator->setUsername(j["username"]);
    return *creator;
}

static Post loadPostFromJson(json j) {
    Post* post = new Post();
    post->setPostId(j["post_id"]);

    Creator creator = loadCreatorFromJson(j["creator"]);
    post->setCreator(creator);
    post->setText(j["text"]);
    post->setTimestamp(j["timestamp"].get<int>());
    post->setPostType(PostType::POST);

    return *post;
}


EM_JS(void, save_in_local_storage_js, (const char* json_cstr), {
    const json = UTF8ToString(json_cstr);
    console.log("Saving all to local storage ...");

    console.log("Saving all posts ...", JSON.parse(json));
    localStorage.setItem('posts', json);
    console.log("All posts saved to local storage.");

    console.log("Saved successfully !");
});

EM_JS(char*, get_posts_from_local_storage_js, (), {
   console.log("Loading posts from local storage");

   const posts_json_str = localStorage.getItem('posts');

   console.log("Loaded posts successfully !");

   const parsedJson = JSON.parse(posts_json_str);

   return stringToNewUTF8(posts_json_str);
});

InMemoryPersistenceService::InMemoryPersistenceService() {
    json postsJson = json::parse(get_posts_from_local_storage_js());
   for (json postJson: postsJson) {
       std::cout << "Loading post: " << postJson.dump() << std::endl;
       this->SavePost(loadPostFromJson(postJson));
   }
}

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

void InMemoryPersistenceService::SaveAllInLocalStorage() {
    json posts_json = json::array();
    for (const auto& post : this->posts) {
        posts_json.push_back(post.toJson());
    }
    save_in_local_storage_js(posts_json.dump().c_str());
}

EMSCRIPTEN_BINDINGS(in_memory_persistence_module) {
    class_<InMemoryPersistenceService>("InMemoryPersistenceService")
        .constructor<>()
        .function("SavePost", &InMemoryPersistenceService::SavePost)
        .function("GetAllPosts", &InMemoryPersistenceService::GetAllPosts)
        .function("GetPostsByUserId", &InMemoryPersistenceService::GetPostsByUserId)
        .function("SaveAllInLocalStorage", &InMemoryPersistenceService::SaveAllInLocalStorage)
    ;

    register_vector<Post>("PostList");
}
