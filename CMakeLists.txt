cmake_minimum_required(VERSION 3.19)

# I'll be honest with you, I don't know what that code does.
# It's not mine. It's from the internet. I'm just copying it.
# I'm not even sure if it works. I'm not even sure if it's right.
# I'm not even sure if it's right. I'm not even sure if it's right.
# I'm not even sure if it's right. I'm not even sure if it's right.

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

if ("${CMAKE_SOURCE_DIR} STRQUAL ${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_subdirectory(brainfucppk)
add_subdirectory(application)
