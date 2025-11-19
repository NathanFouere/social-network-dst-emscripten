#include "PostStorageHandler.hpp"
#include <cstddef>
#include <cstdint>
#include <emscripten/bind.h>
#include <emscripten.h>
#include <nlohmann/json.hpp>

using namespace emscripten;
using nlohmann::json;


EM_ASYNC_JS(void, edit_post_in_indexed_db, (const char* post_json_cstr), {
    const post_json_utf_8 = UTF8ToString(post_json_cstr);

    const db = await new Promise((resolve, reject) => {
        const openRequest = indexedDB.open("store");

        openRequest.onsuccess = () => resolve(openRequest.result);
        openRequest.onerror  = () => reject(openRequest.error);
    });

    await new Promise((resolve, reject) => {
        let transaction = db.transaction("posts", "readwrite");
        let posts = transaction.objectStore("posts");
        let request = posts.put(JSON.parse(post_json_utf_8));
    });
});


EM_ASYNC_JS(void, delete_post_in_indexed_db, (int64_t post_id), {
    const db = await new Promise((resolve, reject) => {
        const openRequest = indexedDB.open("store");

        openRequest.onsuccess = () => resolve(openRequest.result);
        openRequest.onerror  = () => reject(openRequest.error);
    });

    await new Promise((resolve, reject) => {
        let transaction = db.transaction("posts", "readwrite");
        let posts = transaction.objectStore("posts");
        let request = posts.delete(Number(post_id)); // oblider de faire la conversion à cause de big int
    });
});

EM_ASYNC_JS(char*, get_posts_from_indexed_db, (), {
   const db = await new Promise((resolve, reject) => {
       const openRequest = indexedDB.open("store");

       openRequest.onsuccess = () => resolve(openRequest.result);
       openRequest.onerror  = () => reject(openRequest.error);
   });

   const allPosts = await new Promise((resolve, reject) => {
       const transaction = db.transaction("posts", "readonly");
       const store = transaction.objectStore("posts");
       const req = store.getAll();

       req.onsuccess = () => resolve(req.result);
       req.onerror   = () => reject(req.error);
   });

   console.log("IndexedDB posts:", JSON.stringify(allPosts));

   return stringToNewUTF8(JSON.stringify(allPosts));
});

EM_ASYNC_JS(void, create_posts_structure_in_indexed_db, (), {
    const db = await new Promise((resolve, reject) => {
        const openRequest = indexedDB.open("store", 6); // 5 indique la version, il faut voir pour pas la mettre en dur comme un schlag
        openRequest.onsuccess = () => resolve(openRequest.result);
        openRequest.onerror  = () => reject(openRequest.error);
        openRequest.onupgradeneeded = function() {
            let db = openRequest.result;
            if (!db.objectStoreNames.contains('posts')) {
              const postsObjectStore = db.createObjectStore('posts', {keyPath: 'post_id'});
              postsObjectStore.createIndex("post_id", "post_id", { unique: true });
              postsObjectStore.createIndex("creator", "creator", { unique: false } );
              postsObjectStore.createIndex("text", "text", { unique: false });
              postsObjectStore.createIndex("timestamp", "timestamp", { unique: false });
              postsObjectStore.createIndex("post_type", "post_type", { unique: false });
            }
        };
    });

    const allPosts = await new Promise((resolve, reject) => {
        const transaction = db.transaction("posts", "readonly");
        const store = transaction.objectStore("posts");
        const req = store.getAll();

        req.onsuccess = () => resolve(req.result);
        req.onerror   = () => reject(req.error);
    });
});

EM_ASYNC_JS(void, save_post_in_indexed_db, (const char* post_json_cstr), {
    console.log("debut save post in indexeddb");
    const post_json_utf_8 = UTF8ToString(post_json_cstr);

    const db = await new Promise((resolve, reject) => {
        const openRequest = indexedDB.open("store");

        openRequest.onsuccess = () => resolve(openRequest.result);
        openRequest.onerror  = () => reject(openRequest.error);
    });

    await new Promise((resolve, reject) => {
        let transaction = db.transaction("posts", "readwrite");
        let posts = transaction.objectStore("posts");
        let request = posts.add(JSON.parse(post_json_utf_8));
    });
    console.log("fin save post in indexeddb");
});



PostStorageHandler::PostStorageHandler() {
   // charge tous les posts depuis indexed db lors de l'initialisation du service
   create_posts_structure_in_indexed_db();
   auto postsFromIndexedDb = get_posts_from_indexed_db();
   if (postsFromIndexedDb != nullptr) {
       json postsJson = json::parse(postsFromIndexedDb);
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
            edit_post_in_indexed_db(this->posts[i].toJson().dump().c_str());
            return;
        }
    }
}

void PostStorageHandler::DeletePost(int64_t post_id) {
    for (std::size_t i = 0; i < posts.size(); i++) {
        if (this->posts[i].post_id == post_id) {
            std::cout << "delete_post_in_indexed_db" << "   " << this->posts[i].post_id << std::endl;

            delete_post_in_indexed_db(this->posts[i].post_id);
            this->posts.erase(this->posts.begin() + i);
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

void PostStorageHandler::StorePost(const Post &post) {
    this->posts.push_back(post);
    save_post_in_indexed_db(post.toJson().dump().c_str());
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
