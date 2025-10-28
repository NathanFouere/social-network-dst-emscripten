#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class SocialGraphHandler {
  public:
    SocialGraphHandler();
    void InsertUser(int64_t);
    std::vector<int64_t> GetFollowers(const int64_t user_id);
    std::vector<int64_t> GetFollowees(const int64_t user_id);
    void Follow(int64_t user_id, int64_t followee_id);
    void Unfollow(int64_t user_id, int64_t followee_id);
    void FollowWithUsername(const std::string &user_name, const std::string &followee_name);
};
