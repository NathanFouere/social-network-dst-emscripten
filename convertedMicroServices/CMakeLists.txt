cmake_minimum_required(VERSION 3.13)
project(convertedMicroServices)

# Pour aller chercher les packages seulement dans l'env du shell nix (voire https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH_MODE_PACKAGE.html)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NONE) 

find_package(nlohmann_json REQUIRED)

add_executable(
    convertedMicroServices
    Types/Creator/Creator.cpp
    Types/Media/Media.cpp
    Types/UserMention/UserMention.cpp
    Types/Url/Url.cpp
    Types/Post/Post.cpp
    Types/Post/PostType.cpp
    Types/User/User.cpp
    Types/TextServiceReturn/TextServiceReturn.cpp
    UniqueIdHandler/UniqueIdHandler.cpp
    MediaHandler/MediaHandler.cpp
    SocialGraphHandler/SocialGraphHandler.cpp
    UserHandler/UserHandler.cpp
    PostStorageHandler/PostStorageHandler.cpp
    UserMentionHandler/UserMentionHandler.cpp
    ComposePostHandler/ComposePostHandler.cpp
    TextHandler/TextHandler.cpp
    UserTimelineHandler/UserTimelineHandler.cpp
    HomeTimelineHandler/HomeTimelineHandler.cpp
    SessionStorageUserService/SessionStorageUserService.cpp
)

set_target_properties(convertedMicroServices PROPERTIES
    CXX_STANDARD 17
    OUTPUT_NAME convertedMicroServices
)

target_link_libraries(
    convertedMicroServices
    nlohmann_json::nlohmann_json
)

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    set_target_properties(convertedMicroServices PROPERTIES
        LINK_FLAGS "--bind -sALLOW_MEMORY_GROWTH=1 -sMODULARIZE=1 -sEXPORT_ES6=1 -sEXPORTED_RUNTIME_METHODS=[\\\"stringToNewUTF8\\\"]"
    )
endif()
