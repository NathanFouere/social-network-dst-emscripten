cmake_minimum_required(VERSION 3.13)
project(convertedMicroServices)

add_executable(
    convertedMicroServices
    Types/Creator/Creator.cpp
    Types/Media/Media.cpp
    UniqueIdHandler/UniqueIdHandler.cpp
    MediaHandler/MediaHandler.cpp
    SocialGraphHandler/SocialGraphHandler.cpp
    UserHandler/UserHandler.cpp
)

set_target_properties(convertedMicroServices PROPERTIES
    CXX_STANDARD 17
    OUTPUT_NAME convertedMicroServices
)

target_link_libraries(
    convertedMicroServices
)

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    set_target_properties(convertedMicroServices PROPERTIES
        LINK_FLAGS "--bind -sALLOW_MEMORY_GROWTH=1"
    )
endif()
