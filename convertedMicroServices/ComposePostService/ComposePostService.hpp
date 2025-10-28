#pragma once

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../Types/Post/Post.hpp"

class ComposePostService {
  public:
    ComposePostService();

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
};
