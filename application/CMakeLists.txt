set(This BrainfucppkApplication)
project(${This} LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG v3.10.5
)

FetchContent_MakeAvailable(json)

set(Sources
    src/ProjectInterpreter.cpp
    src/BrainfuckProject.cpp
    src/main.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PRIVATE
    Brainfucppk
    nlohmann_json::nlohmann_json
)

target_include_directories(${This} PRIVATE
    ${CMAKE_SOURCE_DIR}/brainfucppk/include
    ${CMAKE_BINARY_DIR}/_deps/json-src/single_include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
