#include "core/Implementation.hpp"

#include "core/Interpreter.hpp"
#include "core/Errors.hpp"

#include "implementations/StandardImplementation.hpp"
#include "implementations/Ext1Implementation.hpp"

BRAINFUCPPK_BEGIN

const std::map<std::string, ImplementationEnum> c_Implementations = {
    { "Standard",  ImplementationEnum::Standard  },
    { "Extended1", ImplementationEnum::Extended1 },
};

ImplementationEnum GetImplementationFromString(const std::string& name)
{
    if (c_Implementations.find(name) == c_Implementations.end())
        throw BasicError::Create("unknown brainfuck implementation!");

    return c_Implementations.at(name);
}

Implementation::Implementation(const WarpableIterator<unsigned char>& pointer, std::ostream& output, std::istream& input)
    : p_Pointer{ pointer }, p_OutputStream{ output }, p_InputStream{ input } {}

Implementation* Implementation::Create(Interpreter* owner, const std::string& name)
{
    return Implementation::Create(owner, GetImplementationFromString(name));
}

Implementation* Implementation::Create(Interpreter* owner, ImplementationEnum implementation)
{
    auto pointer{ owner->m_Pointer      };
    auto output { owner->m_OutputStream };
    auto input  { owner->m_InputStream  };

    switch (implementation)
    {
    case ImplementationEnum::Standard:  return new StandardImplementation(pointer, *output, *input);
    case ImplementationEnum::Extended1: return new Ext1Implementation(pointer, *output, *input);

    default:
        throw BasicError::Create("could not retrieve existing implementation!");
    }

    /* redundant, but it's nice to return something */
    return nullptr;
}

BRAINFUCPPK_END
