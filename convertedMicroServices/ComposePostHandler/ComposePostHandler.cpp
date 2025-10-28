#include "ComposePostHandler.hpp"
#include <emscripten/bind.h>
#include <iostream>
#include <stdexcept>
#include "../Types/Post/Post.hpp"

using namespace emscripten;

ComposePostHandler::ComposePostHandler() {}

void ComposePostHandler::ComposePost(
    int64_t req_id,
    const std::string &username,
    int64_t user_id,
    const std::string &text,
    const std::vector<int64_t> &media_ids,
    const std::vector<std::string> &media_types,
    PostType::type post_type,
    const std::map<std::string, std::string> &carrier
) {
    if (media_ids.size() != media_types.size()) {
        throw std::invalid_argument("The lengths of media_id list and media_type list are not equal");
    }

    std::cout << "ComposePost (handler) called: req_id=" << req_id
              << " username=" << username
              << " user_id=" << user_id << std::endl;
    std::cout << "Text: " << text << std::endl;
    std::cout << "Post type: " << static_cast<int>(post_type) << std::endl;
    std::cout << "Media count: " << media_ids.size() << std::endl;

    if (!carrier.empty()) {
        std::cout << "Carrier headers:" << std::endl;
        for (const auto &kv : carrier) {
            std::cout << "  " << kv.first << ": " << kv.second << std::endl;
        }
    }
}

void ComposePostHandler::ComposePost(
    int64_t req_id,
    const std::string &username,
    int64_t user_id,
    const std::string &text,
    emscripten::val media_ids_js,
    emscripten::val media_types_js,
    PostType::type post_type
) {
    // Convertir les arrays JS en std::vector C++
    auto len = media_ids_js["length"].as<unsigned>();
    std::vector<int64_t> media_ids;
    media_ids.reserve(len);
    std::vector<std::string> media_types;
    media_types.reserve(len);
    for (unsigned i = 0; i < len; ++i) {
        media_ids.push_back(media_ids_js[i].as<int64_t>());
        media_types.push_back(media_types_js[i].isUndefined() ? std::string("") : media_types_js[i].as<std::string>());
    }
    std::map<std::string, std::string> empty_carrier;
    // Déléguer vers la version principale
    ComposePost(req_id, username, user_id, text, media_ids, media_types, post_type, empty_carrier);
}

void ComposePostHandler::ComposePostSimple(
    int64_t req_id,
    const std::string &username,
    int64_t user_id,
    const std::string &text,
    emscripten::val media_ids_js,
    emscripten::val media_types_js
) {
    // media_ids_js et media_types_js sont des tableaux JS natifs
    auto length = media_ids_js["length"].as<unsigned>();
    std::cout << "[Mock] ComposePostSimple called: req_id=" << req_id
              << ", username=" << username
              << ", user_id=" << user_id
              << ", text=\"" << text << "\""
              << ", media_count=" << length
              << std::endl;

    // Exemple: afficher le premier élément si présent
    if (length > 0) {
        auto id0 = media_ids_js[0].as<int64_t>();
        auto type0 = media_types_js[0].as<std::string>();
        std::cout << "[Mock] First media => id=" << id0 << ", type=" << type0 << std::endl;
    }
}

EMSCRIPTEN_BINDINGS(compose_post_handler) {
    class_<ComposePostHandler>("ComposePostHandler")
        .constructor<>()
        .function("ComposePost", select_overload<void(int64_t,const std::string&,int64_t,const std::string&,const std::vector<int64_t>&,const std::vector<std::string>&,PostType::type,const std::map<std::string,std::string>&)>(&ComposePostHandler::ComposePost))
        .function("ComposePost", select_overload<void(int64_t,const std::string&,int64_t,const std::string&,emscripten::val,emscripten::val,PostType::type)>(&ComposePostHandler::ComposePost))
        .function("ComposePostSimple", &ComposePostHandler::ComposePostSimple);
}

