add_executable(
        TestService
        TestService.cpp
        ${THRIFT_GEN_CPP_DIR}/TestService.cpp
)

target_include_directories(
        TestService PRIVATE
        /usr/local/include/jaegertracing
)

target_link_libraries(
        TestService
        nlohmann_json::nlohmann_json
        ${THRIFT_LIB}
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES}
        Boost::log
        Boost::log_setup
        jaegertracing
)

install(TARGETS TestService DESTINATION ./)