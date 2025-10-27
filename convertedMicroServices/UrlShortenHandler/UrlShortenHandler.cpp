#include "UrlShortenHandler.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

UrlShortenHandler::UrlShortenHandler() {

}

std::vector<Url> UrlShortenHandler::ComposeUrls(const std::vector<std::string> &urls) {
    // TODO Implement
    std::vector<Url> shortened_urls = {};
    return shortened_urls;
}

std::vector<std::string> UrlShortenHandler::GetExtendedUrls(const std::vector<std::string> &shortened_ids) {
    // TODO Implement (pour le coup on le fera pas, ce n'est pas implémenté nons plus dans le service originel)
    std::vector<std::string> extended_urls = {};
    return extended_urls;
}

EMSCRIPTEN_BINDINGS(url_shorten_handler_module) {
    class_<UrlShortenHandler>("UrlShortenHandler")
        .constructor<>()
        .function("ComposeUrls", &UrlShortenHandler::ComposeUrls)
        .function("GetExtendedUrls", &UrlShortenHandler::GetExtendedUrls);
}
