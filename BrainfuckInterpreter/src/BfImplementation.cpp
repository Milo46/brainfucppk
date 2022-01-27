#include "BfImplementation.hpp"
#include "BfInterpreter.hpp"

#include "BfConfiguration.hpp"

#include "StandardBfInterpretation.hpp"

BrainfuckImplementation* GetBrainfuckImplementation(BrainfuckInterpreter* interpreter)
{
    switch (BrainfuckConfiguration::GetBrainfuckAPI())
    {
    case BrainfuckAPI::Standard: return new StandardBrainfuckImplementation(interpreter);

    default:
        throw std::exception{ "Unknown BrainfuckAPI!" };
    }
}

BrainfuckImplementation::BrainfuckImplementation(BrainfuckInterpreter* interpreter)
    : m_Interpreter(interpreter), p_Memory(interpreter->m_Memory), p_Pointer(interpreter->m_Pointer) {}
