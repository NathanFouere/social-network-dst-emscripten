#include "PostStorageHandler.hpp"
#include <cstddef>
#include <cstdint>
#include <emscripten/bind.h>
#include <emscripten.h>
#include <nlohmann/json.hpp>

using namespace emscripten;
using nlohmann::json;


EM_JS(void, save_posts_in_local_storage, (const char* posts_json_cstr), {
    const posts_json_utf_8 = UTF8ToString(posts_json_cstr);
    console.log("Saving all to local storage ...");

    console.log("Saving all posts ...", JSON.parse(posts_json_utf_8));
    localStorage.setItem('posts', posts_json_utf_8);
    console.log("All posts saved to local storage.");

    console.log("Saved successfully !");
});

EM_JS(char*, get_posts_from_local_storage_js, (), {
   console.log("Loading posts from local storage");

   const posts_json_str = localStorage.getItem('posts');
   console.log(posts_json_str);
   console.log("Loaded posts successfully !", posts_json_str);
   if(null == posts_json_str) {
       return null;
   }
   return stringToNewUTF8(posts_json_str);
});

PostStorageHandler::PostStorageHandler() {
   // charge tous les posts depuis le local storage lors de l'initialisation du service
   auto postsFromLocalStorage = get_posts_from_local_storage_js();
   if (postsFromLocalStorage != nullptr) {
       json postsJson = json::parse(postsFromLocalStorage);
       for (json postJson: postsJson) {
           this->posts.push_back(Post::fromJson(postJson));
       }
   }

}

std::vector<Post> PostStorageHandler::GetPostsBetweenIdx(int start_idx, int stop_idx) const {
    std::vector<Post> postToReturn;
    for(std::size_t i = start_idx; i < stop_idx; i++) {
        if (i >= this->posts.size()) {
            return postToReturn;
        }
        postToReturn.push_back(this->posts.at(i));
    }

    return postToReturn;
}

std::vector<Post> PostStorageHandler::GetAllPosts() const {
    return this->posts;
}

void PostStorageHandler::EditPostText(int64_t post_id, std::string newText) {
    for (std::size_t i = 0; i < posts.size(); i++) {
        if (this->posts[i].post_id == post_id) {
            this->posts[i].setText(newText);
            this->SaveAllInLocalStorage();
            return;
        }
    }
}

void PostStorageHandler::DeletePost(int64_t post_id) {
    for (std::size_t i = 0; i < posts.size(); i++) {
        if (this->posts[i].post_id == post_id) {
            this->posts.erase(this->posts.begin() + i);
            this->SaveAllInLocalStorage();
            return;
        }
    }
}

Post* PostStorageHandler::GetPostById(int64_t post_id) {
    for (Post& post : this->posts) {
        if (post.post_id == post_id) {
            return &post;
        }
    }
    return nullptr;
}

void PostStorageHandler::SaveAllInLocalStorage() {
    json posts_json = json::array();
    for (const auto& post : this->posts) {
        posts_json.push_back(post.toJson());
    }
    save_posts_in_local_storage(posts_json.dump().c_str());
}

void PostStorageHandler::StorePost(const Post &post) {
    this->posts.push_back(post);
    this->SaveAllInLocalStorage();
}

Post* PostStorageHandler::ReadPost(int64_t post_id) {
    for (Post& post : this->posts) {
        if (post.post_id == post_id) {
            return &post;
        }
    }
    return nullptr;
}

EMSCRIPTEN_BINDINGS(post_storage_module) {
    class_<PostStorageHandler>("PostStorageHandler")
        .constructor<>()
        .function("StorePost", &PostStorageHandler::StorePost)
        .function("DeletePost", &PostStorageHandler::DeletePost)
        .function("EditPostText", &PostStorageHandler::EditPostText)
    ;
}
