#include "Creator.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(creator_module) {
    class_<Creator>("Creator")
    .constructor<>();
}
