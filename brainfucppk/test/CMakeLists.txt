set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

set(Sources
    SemanticVersionTest.cpp
)

add_executable(${BINARY} ${Sources})
add_test(
    NAME ${BINARY}
    COMMAND ${BINARY}
)

target_link_directories(${BINARY} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/vendor/json/include
)

target_link_libraries(${BINARY} PUBLIC
    gtest_main
    ${CMAKE_PROJECT_NAME}_lib
)
