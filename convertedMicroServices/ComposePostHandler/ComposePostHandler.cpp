#include "ComposePostHandler.hpp"
#include <emscripten/bind.h>
#include <iostream>
#include <vector>
#include "../Types/Post/Post.hpp"

using namespace emscripten;

ComposePostHandler::ComposePostHandler(
    UserTimelineHandler& userTimelineHandler,
    UserHandler& userHandler,
    UniqueIdHandler& uniqueIdHandler,
    MediaHandler& mediaHandler,
    TextHandler& textHandler,
    HomeTimelineHandler& homeTimelineHandler
) : userTimelineHandler(userTimelineHandler),
    userHandler(userHandler),
    uniqueIdHandler(uniqueIdHandler),
    mediaHandler(mediaHandler),
    textHandler(textHandler),
    homeTimelineHandler(homeTimelineHandler
) {}

void ComposePostHandler::ComposePost(
    int64_t req_id,
    const std::string &username,
    int64_t user_id,
    const std::string &text,
    const std::vector<int64_t> &media_ids,
    const std::vector<std::string> &media_types,
    PostType::type post_type
) {
    if (media_ids.size() != media_types.size()) {
        std::cerr << "ComposePost: media_ids and media_types size mismatch" << std::endl;
        return;
    }

    std::cout << "ComposePost called: req_id=" << req_id
              << ", username=" << username
              << ", user_id=" << user_id
              << ", text=\"" << text << "\""
              << ", post_type=" << static_cast<int>(post_type)
              << ", media_count=" << media_ids.size()
              << std::endl;

    if (!media_ids.empty()) {
        std::cout << "First media => id=" << media_ids[0]
                  << ", type=" << (media_types.empty() ? std::string("") : media_types[0])
                  << std::endl;
    }
}

EMSCRIPTEN_BINDINGS(compose_post_handler) {
    class_<ComposePostHandler>("ComposePostHandler")
        .constructor<UserTimelineHandler&, UserHandler&, UniqueIdHandler&, MediaHandler&, TextHandler&, HomeTimelineHandler&>()
        .function("ComposePost", &ComposePostHandler::ComposePost);
}
