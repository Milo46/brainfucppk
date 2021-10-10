#include <iostream>

using enum_t = size_t;

enum BrainfuckTokens {
    IncrementPointer = 0u,
    DecrementPointer,
    IncrementValue,
    DecrementValue,
    GetOutput,
    GetInput,
    StartLoop,
    EndLoop,

    Size
};

constexpr const char* g_Tokens = "><+->,[]";

int main(int argc, char** argv)
{
    char memory[30000];
    char* ptr = memory;

    char token = '+';
    switch (token)
    {
    case g_Tokens[BrainfuckTokens::IncrementPointer]:
        ++ptr;
        break;

    case g_Tokens[BrainfuckTokens::DecrementPointer]:
        break;

    case g_Tokens[BrainfuckTokens::IncrementValue]:
        break;
    }

    return EXIT_SUCCESS;
}
