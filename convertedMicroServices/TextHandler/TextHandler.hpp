#pragma once

#include "../UrlShortenHandler/UrlShortenHandler.hpp"
#include "../UserMentionHandler/UserMentionHandler.hpp"
#include "../Types/TextServiceReturn/TextServiceReturn.hpp"

class TextHandler {
    public:
        TextHandler(
            UrlShortenHandler& urlShortenHandler, 
            UserMentionHandler& userMentionHandler
        );
        TextServiceReturn ComposeText(const std::string &text);
        
    private:
        UrlShortenHandler& urlShortenHandler;
        UserMentionHandler& userMentionHandler;
};