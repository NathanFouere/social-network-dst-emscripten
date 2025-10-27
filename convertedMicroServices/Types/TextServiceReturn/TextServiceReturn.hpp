#pragma once

#include <string>
#include <vector>
#include "../UserMention/UserMention.hpp"
#include "../Url/Url.hpp"

class TextServiceReturn {
  public:
    TextServiceReturn();
    void setText(const std::string& _text);
    std::string getText() const;
    void setUserMentions(const std::vector<UserMention>& _user_mentions);
    std::vector<UserMention> getUserMentions() const;
    void setUrls(const std::vector<Url>& _urls);
    std::vector<Url> getUrls() const;
    
  private:
    std::string text;
    std::vector<UserMention>  user_mentions;
    std::vector<Url>  urls;
    
};