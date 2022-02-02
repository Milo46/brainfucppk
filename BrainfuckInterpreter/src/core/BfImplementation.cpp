#include "BfImplementation.hpp"

#include "core/BfInterpreter.hpp"
#include "core/BfConfiguration.hpp"

#include "implementations/StandardBfImplementation.hpp"

const std::map<std::string, BrainfuckImplementationEnum> c_BrainfuckImplementations = {
    { "Standard", BrainfuckImplementationEnum::Standard },
    { "Extended", BrainfuckImplementationEnum::Extended }
};

BrainfuckImplementationEnum GetBrainfuckImplementationFromString(const std::string& name)
{
    if (c_BrainfuckImplementations.find(name) == c_BrainfuckImplementations.end())
        throw std::exception{ "Unknown brainfuck implementation!" };

    return c_BrainfuckImplementations.at(name);
}

BrainfuckImplementation* GetBrainfuckImplementation(const std::string& name, unsigned char* pointer)
{
    return GetBrainfuckImplementation(GetBrainfuckImplementationFromString(name), pointer);
}

BrainfuckImplementation* GetBrainfuckImplementation(BrainfuckImplementationEnum implementation, unsigned char* pointer)
{
    switch (implementation)
    {
    case BrainfuckImplementationEnum::Standard: return new StandardBrainfuckImplementation(pointer);
        //case BrainfuckImplementationEnum::Extended: return new ExtendedBrainfuckImplementation(pointer);

    default:
        throw std::exception{ "Could not retrieve existing implementation! " };
    }
}

BrainfuckImplementation::BrainfuckImplementation(unsigned char* pointer)
    : p_Pointer(pointer) {}
