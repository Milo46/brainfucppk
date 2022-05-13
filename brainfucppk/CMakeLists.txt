set(This Brainfucppk)
project(${This} LANGUAGES CXX)

set(Sources
    src/core/Errors.cpp
    src/core/Implementation.cpp
    src/core/Interpreter.cpp

    src/implementations/Ext1Implementation.cpp
    src/implementations/StandardImplementation.cpp

    src/utility/SemanticVersion.cpp
)

add_library(${This} STATIC ${Sources})

target_include_directories(${This} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/include
)
