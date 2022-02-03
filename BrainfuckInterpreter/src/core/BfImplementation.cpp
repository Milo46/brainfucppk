#include "BfImplementation.hpp"

#include "core/BfInterpreter.hpp"

#include "implementations/StandardBfImplementation.hpp"
#include "implementations/Ext1BfImplementation.hpp"

const std::map<std::string, BFImplementationEnum> c_BrainfuckImplementations = {
    { "Standard",  BFImplementationEnum::Standard  },
    { "Extended1", BFImplementationEnum::Extended1 }
};

BFImplementationEnum GetBrainfuckImplementationFromString(const std::string& name)
{
    if (c_BrainfuckImplementations.find(name) == c_BrainfuckImplementations.end())
        throw std::exception{ "Unknown brainfuck implementation!" };

    return c_BrainfuckImplementations.at(name);
}

BrainfuckImplementation* GetBrainfuckImplementation(const std::string& name, unsigned char* pointer)
{
    return GetBrainfuckImplementation(GetBrainfuckImplementationFromString(name), pointer);
}

BrainfuckImplementation* GetBrainfuckImplementation(BFImplementationEnum implementation, unsigned char* pointer)
{
    switch (implementation)
    {
    case BFImplementationEnum::Standard:  return new StandardBrainfuckImplementation(pointer);
    case BFImplementationEnum::Extended1: return new Ext1BrainfuckImplementation(pointer);
    //case BFImplementationEnum::Extended2: return new Ext2BrainfuckImplementation(pointer);
    //case BFImplementationEnum::Extended3: return new Ext3BrainfuckImplementation(pointer);

    default:
        throw std::exception{ "Could not retrieve existing implementation! " };
    }
}

BrainfuckImplementation::BrainfuckImplementation(unsigned char* pointer)
    : p_Pointer(pointer) {}
