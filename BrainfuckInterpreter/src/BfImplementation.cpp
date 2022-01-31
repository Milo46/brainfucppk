#include "BfImplementation.hpp"
#include "BfInterpreter.hpp"

#include "BfConfiguration.hpp"

#include "StandardBfImplementation.hpp"

BrainfuckImplementation* GetBrainfuckImplementation(unsigned char* pointer)
{
    switch (BrainfuckConfiguration::GetBrainfuckAPI())
    {
    case BrainfuckAPI::Standard: return new StandardBrainfuckImplementation(pointer);

    default:
        throw std::exception{ "Unknown BrainfuckAPI!" };
    }
}

BrainfuckImplementation::BrainfuckImplementation(unsigned char* pointer)
    : p_Pointer(pointer)
{
    if (!pointer) std::cout << "Pointer is nullptr!\n";
}

