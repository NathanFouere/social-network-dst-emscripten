#include "TextHandler.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

TextHandler::TextHandler(
    UrlShortenHandler& urlShortenHandler,
    UserMentionHandler& userMentionHandler):
        urlShortenHandler(urlShortenHandler),
        userMentionHandler(userMentionHandler)
{

}

TextServiceReturn TextHandler::ComposeText(const std::string &text) {
    // TODO Implement
    TextServiceReturn* falseReturn = new TextServiceReturn();
    return *falseReturn;
}

EMSCRIPTEN_BINDINGS(text_handler_module) {
    class_<TextHandler>("TextHandler")
        .constructor<UrlShortenHandler&, UserMentionHandler&>()
        .function("ComposeText", &TextHandler::ComposeText);
}
