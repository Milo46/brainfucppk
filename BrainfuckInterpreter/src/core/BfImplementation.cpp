#include "BfImplementation.hpp"

#include "core/BfInterpreter.hpp"
#include "core/BfConfiguration.hpp"

#include "implementations/StandardBfImplementation.hpp"

BrainfuckImplementation* GetBrainfuckImplementation(unsigned char* pointer)
{
    switch (BrainfuckConfiguration::GetBrainfuckAPI())
    {
    case BrainfuckAPI::Standard: return new StandardBrainfuckImplementation(pointer);

    default:
        throw std::exception{ "Unknown BrainfuckAPI!" };
    }
}

enum Implementations
{
    Standard = 0u,
    Extended
};

const std::map<std::string, Implementations> g_BrainfuckImplementations = {
    { "Standard", Implementations::Standard },
    { "Extended", Implementations::Extended }
};

BrainfuckImplementation* GetBrainfuckImplementation(const std::string& name, unsigned char* pointer)
{
    if (g_BrainfuckImplementations.find(name) == g_BrainfuckImplementations.end())
        throw std::exception{ "Unknown brainfuck implementation!" };

    switch (g_BrainfuckImplementations.at(name))
    {
    case Implementations::Standard: return new StandardBrainfuckImplementation(pointer);
    //case Implementations::Extended: return new ExtendedBrainfuckImplementation(pointer);

    default:
        throw std::exception{ "Could not retrieve existing implementation! " };
    }
}

BrainfuckImplementation::BrainfuckImplementation(unsigned char* pointer)
    : p_Pointer(pointer) {}

void BrainfuckImplementation::InterpretTokens(const std::string& source)
{
    for (std::size_t i = 0u; i < source.size(); ++i)
    {
        if (auto callback = ResolveToken(source[i]))
            callback(source, i);
    }
}
