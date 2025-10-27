#pragma once

#include <vector>
#include "../Types/Url/Url.hpp"
#include <string>

class UrlShortenHandler {
    public:
        UrlShortenHandler();
        std::vector<Url> ComposeUrls(const std::vector<std::string> &urls);
        std::vector<std::string> GetExtendedUrls(const std::vector<std::string> &shortened_ids);
};
