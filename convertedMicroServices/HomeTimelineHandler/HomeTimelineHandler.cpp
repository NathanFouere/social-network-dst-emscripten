#include "HomeTimelineHandler.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

HomeTimelineHandler::HomeTimelineHandler(
    PostStorageHandler& postStorageHandler, SocialGraphHandler& socialGraphHandler)
    : postStorageHandler(postStorageHandler), socialGraphHandler(socialGraphHandler) {};
    
std::vector<Post> HomeTimelineHandler::ReadHomeTimeline(int64_t user_id, int start_idx, int stop_idx) {
    std::cout << "ReadHomeTimeline appelé" << std::endl;
    Post* fakePost = new Post();
    
    std::vector<Post> fakePosts = { *fakePost };
    
    return fakePosts;
};

void HomeTimelineHandler::WriteHomeTimeline(int64_t post_id, int64_t user_id, int64_t timestamp, const std::vector<int64_t>& user_mentions_id) {
    std::cout << "WriteHomeTimeline appelé" << std::endl;
};

EMSCRIPTEN_BINDINGS(home_timeline_module) {
    class_<HomeTimelineHandler>("HomeTimelineHandler")
        .constructor<PostStorageHandler&, SocialGraphHandler&>()
        .function("ReadHomeTimeline", &HomeTimelineHandler::ReadHomeTimeline)
        .function("WriteHomeTimeline", &HomeTimelineHandler::WriteHomeTimeline);
}