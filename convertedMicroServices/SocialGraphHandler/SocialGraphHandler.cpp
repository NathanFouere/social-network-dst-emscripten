#include "SocialGraphHandler.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

SocialGraphHandler::SocialGraphHandler() {

}

void SocialGraphHandler::InsertUser(int64_t user_id) {
    std::cout << "Insert User Appelé !" << std::endl;
}

EMSCRIPTEN_BINDINGS(social_graph_module) {
    class_<SocialGraphHandler>("SocialGraphHandler")
    .constructor<>()
    .function("InsertUser", &SocialGraphHandler::InsertUser);
}
