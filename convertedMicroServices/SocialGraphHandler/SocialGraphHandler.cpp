#include "SocialGraphHandler.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

SocialGraphHandler::SocialGraphHandler() {

}

void SocialGraphHandler::InsertUser(int64_t user_id) {
    std::cout << "Insert User Appelé !" << std::endl;
}

std::vector<int64_t> SocialGraphHandler::GetFollowers(const int64_t user_id) {
    std::cout << "Get Followers Appelé !" << std::endl;
    return std::vector<int64_t>{};
}

std::vector<int64_t> SocialGraphHandler::GetFollowees(const int64_t user_id) {
    std::cout << "Get Followees Appelé !" << std::endl;
    return std::vector<int64_t>{};
}

void SocialGraphHandler::Follow(int64_t user_id, int64_t followee_id) {
    std::cout << "Follow Appelé !" << std::endl;
}

void SocialGraphHandler::Unfollow(int64_t user_id, int64_t followee_id) {
    std::cout << "Unfollow Appelé !" << std::endl;
}

void SocialGraphHandler::FollowWithUsername(const std::string &user_name, const std::string &followee_name) {
    std::cout << "Follow With Username Appelé !" << std::endl;
}

EMSCRIPTEN_BINDINGS(social_graph_module) {
    class_<SocialGraphHandler>("SocialGraphHandler")
        .constructor<>()
        .function("InsertUser", &SocialGraphHandler::InsertUser)
        .function("GetFollowers", &SocialGraphHandler::GetFollowers)
        .function("GetFollowees", &SocialGraphHandler::GetFollowees)
        .function("Follow", &SocialGraphHandler::Follow)
        .function("Unfollow", &SocialGraphHandler::Unfollow)
        .function("FollowWithUsername", &SocialGraphHandler::FollowWithUsername)
    ;
}
