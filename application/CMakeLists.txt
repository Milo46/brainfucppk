set(This BrainfucppkApplication)
project(${This} LANGUAGES CXX)

set(Sources
    src/main.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} Brainfucppk)

target_include_directories(${This} PRIVATE
    ${CMAKE_SOURCE_DIR}/brainfucppk/include
)
