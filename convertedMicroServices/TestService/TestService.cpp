#include "TestService.hpp"
#include <string>
#include <emscripten/bind.h>

using namespace emscripten;

TestService::TestService() {
    
}

std::string TestService::TestFunction() {
    return "Bonjour";
}


EMSCRIPTEN_BINDINGS() {
  class_<TestService>("TestService")
    .constructor<>()
    .function("TestFunction", &TestService::TestFunction)
  ;
};