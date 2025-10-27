#include "TextServiceReturn.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

TextServiceReturn::TextServiceReturn(): text() {
}

void TextServiceReturn::setText(const std::string& _text) {
    this->text = _text;
}

std::string TextServiceReturn::getText() const {
    return this->text;
}

void TextServiceReturn::setUserMentions(const std::vector<UserMention>& _user_mentions) {
    this->user_mentions = _user_mentions;
}

std::vector<UserMention> TextServiceReturn::getUserMentions() const {
    return this->user_mentions;
}

void TextServiceReturn::setUrls(const std::vector<Url>& _urls) {
    this->urls = _urls;
}

std::vector<Url> TextServiceReturn::getUrls() const {
    return this->urls;
}

EMSCRIPTEN_BINDINGS(text_service_return_module) {
    class_<TextServiceReturn>("TextServiceReturn")
        .constructor<>()
        .property("text", &TextServiceReturn::getText, &TextServiceReturn::setText)
        .property("user_mentions", &TextServiceReturn::getUserMentions, &TextServiceReturn::setUserMentions)
        .property("urls", &TextServiceReturn::getUrls, &TextServiceReturn::setUrls
    );
}