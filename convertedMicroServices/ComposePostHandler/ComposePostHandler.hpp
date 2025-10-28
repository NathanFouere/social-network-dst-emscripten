#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "../Types/Post/Post.hpp"
#include "../UserTimelineHandler/UserTimelineHandler.hpp"
#include "../UserHandler/UserHandler.hpp"
#include "../UniqueIdHandler/UniqueIdHandler.hpp"
#include "../MediaHandler/MediaHandler.hpp"
#include "../TextHandler/TextHandler.hpp"
#include "../HomeTimelineHandler/HomeTimelineHandler.hpp"


class ComposePostHandler {
    public:
        ComposePostHandler(
            UserTimelineHandler& userTimelineHandler,
            UserHandler& userHandler,
            UniqueIdHandler& uniqueIdHandler,
            MediaHandler& mediaHandler,
            TextHandler& textHandler,
            HomeTimelineHandler& homeTimelineHandler
        );
    
        void ComposePost(
            int64_t req_id,
            const std::string &username,
            int64_t user_id,
            const std::string &text,
            const std::vector<int64_t> &media_ids,
            const std::vector<std::string> &media_types,
            PostType::type post_type
        );
    private:
        UserTimelineHandler& userTimelineHandler;
        UserHandler& userHandler;
        UniqueIdHandler& uniqueIdHandler;
        MediaHandler& mediaHandler;
        TextHandler& textHandler;
        HomeTimelineHandler& homeTimelineHandler;
};
