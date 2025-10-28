#include "ComposePostService.hpp"
#include <emscripten/bind.h>
#include <iostream>
#include <stdexcept>
#include "../Types/Post/Post.hpp"

using namespace emscripten;

ComposePostService::ComposePostService() {
}

void ComposePostService::ComposePost(
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

    std::cout << "ComposePost called: req_id=" << req_id << " username=" << username << " user_id=" << user_id << std::endl;
    std::cout << "Text: " << text << std::endl;
    std::cout << "Post type: " << static_cast<int>(post_type) << std::endl;
    std::cout << "Media count: " << media_ids.size() << std::endl;

    if (!carrier.empty()) {
        std::cout << "Carrier headers:" << std::endl;
        for (const auto &kv : carrier) {
            std::cout << "  " << kv.first << ": " << kv.second << std::endl;
        }
    }

    // Simulation du comportement
    // Afin d'être complet, il faudra rajouter plus tard les liens avec les autres microservices
}

EMSCRIPTEN_BINDINGS(compose_post_service) {
    class_<ComposePostService>("ComposePostService")
        .constructor<>()
        .function("ComposePost", &ComposePostService::ComposePost);
}
