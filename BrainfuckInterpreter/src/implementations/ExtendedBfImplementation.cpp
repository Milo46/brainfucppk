#include "ExtendedBfImplementation.hpp"

#include "core/BfInterpreter.hpp"

ExtendedBrainfuckImplementation::ExtendedBrainfuckImplementation(unsigned char* pointer)
    : StandardBrainfuckImplementation(pointer) {}

bool ExtendedBrainfuckImplementation::ResolveToken(const std::string& source, std::size_t& index)
{
    if (StandardBrainfuckImplementation::ResolveToken(source, index))
        return true;

    switch (source[index])
    {
    case '@': break;
    case '$': break;
    case '!': break;
    case '}': break;
    case '{': break;
    case '~': break;
    case '^': break;
    case '&': break;
    case '|': break;

    default: return false;
    }

    return true;
}
