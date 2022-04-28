set(This Brainfucppk)
project(${This} LANGUAGES CXX)

set(Sources
    src/core/BfErrors.cpp
    src/core/BfImplementation.cpp
    src/core/BfInterpreter.cpp
    src/implementations/Ext1BfImplementation.cpp
    src/implementations/StandardBfImplementation.cpp
    src/utility/FileData.cpp
)

add_library(${This} STATIC ${Sources})

target_include_directories(${This} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/include
)
