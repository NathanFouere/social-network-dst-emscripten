#pragma once

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <emscripten/val.h>
#include "../Types/Post/Post.hpp"

class ComposePostHandler {
  public:
    ComposePostHandler();

    void ComposePost(
        int64_t req_id,
        const std::string &username,
        int64_t user_id,
        const std::string &text,
        const std::vector<int64_t> &media_ids,
        const std::vector<std::string> &media_types,
        PostType::type post_type,
        const std::map<std::string, std::string> &carrier
    );

    // Version simple pour tests: accepte des arrays JS natifs et mock les autres paramètres
    void ComposePostSimple(
        int64_t req_id,
        const std::string &username,
        int64_t user_id,
        const std::string &text,
        emscripten::val media_ids_js,
        emscripten::val media_types_js
    );

    void ComposePost(
        int64_t req_id,
        const std::string &username,
        int64_t user_id,
        const std::string &text,
        emscripten::val media_ids_js,
        emscripten::val media_types_js,
        PostType::type post_type
    );
};
