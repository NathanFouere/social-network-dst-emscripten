#include "HomeTimelineHandler.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

HomeTimelineHandler::HomeTimelineHandler(
    PostStorageHandler& postStorageHandler, 
    SocialGraphHandler& socialGraphHandler,
    InMemoryPersistenceService& inMemoryPersistenceService)
    : postStorageHandler(postStorageHandler), 
    socialGraphHandler(socialGraphHandler), 
    inMemoryPersistenceService(inMemoryPersistenceService) 
{};
    
std::vector<Post> HomeTimelineHandler::ReadHomeTimeline(int64_t user_id, int start_idx, int stop_idx) {
    std::cout << "ReadHomeTimeline appelé" << std::endl;
    // TODO => il faudra ajouter un tri ici et voir utilié start et stop
    std::vector<Post> posts = this->inMemoryPersistenceService.GetAllPosts();
        
    return posts;
};

void HomeTimelineHandler::WriteHomeTimeline(int64_t post_id, int64_t user_id, int64_t timestamp, const std::vector<int64_t>& user_mentions_id) {
    std::cout << "WriteHomeTimeline appelé" << std::endl;
};

EMSCRIPTEN_BINDINGS(home_timeline_module) {
    class_<HomeTimelineHandler>("HomeTimelineHandler")
        .constructor<PostStorageHandler&, SocialGraphHandler&, InMemoryPersistenceService&>()
        .function("ReadHomeTimeline", &HomeTimelineHandler::ReadHomeTimeline)
        .function("WriteHomeTimeline", &HomeTimelineHandler::WriteHomeTimeline);
}