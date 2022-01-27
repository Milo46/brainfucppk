#include "StandardBfInterpretation.hpp"

#include <iostream>

StandardBrainfuckImplementation::StandardBrainfuckImplementation(BrainfuckInterpreter* interpreter)
    : BrainfuckImplementation(interpreter) {}

void StandardBrainfuckImplementation::IncrementPointer(const std::string& source, std::size_t& index) { ++p_Pointer; }
void StandardBrainfuckImplementation::DecrementPointer(const std::string& source, std::size_t& index) { --p_Pointer; }
void StandardBrainfuckImplementation::IncrementValue(const std::string& source, std::size_t& index) { ++(*p_Pointer); }
void StandardBrainfuckImplementation::DecrementValue(const std::string& source, std::size_t& index) { --(*p_Pointer); }

void StandardBrainfuckImplementation::Write(const std::string& source, std::size_t& index) { std::cout << *p_Pointer; }
void StandardBrainfuckImplementation::Read(const std::string& source, std::size_t& index)  { std::cin  >> *p_Pointer; }

void StandardBrainfuckImplementation::BeginLoop(const std::string& source, std::size_t& index, std::size_t prevIndex)
{
    std::size_t subSectionEndIndex = index;
    std::size_t bracketLevel       = 1u;

    while (bracketLevel > 0 && ++subSectionEndIndex)
    {
        if (subSectionEndIndex == source.size())
            throw BrainfuckInterpreter::Error{ "Failed to find ending bracket!", prevIndex + index };

        switch (source[subSectionEndIndex])
        {
            case BrainfuckToken::BeginLoop: ++bracketLevel; break;
            case BrainfuckToken::EndLoop:   --bracketLevel; break;
        }
    }

    // Automatically omits blank loops
    if (subSectionEndIndex - 1 != index) while (*p_Pointer != 0)
        m_Interpreter->InterpretSection(source.substr(index + 1, subSectionEndIndex - index - 1), prevIndex + index);

    index = subSectionEndIndex;
}

void StandardBrainfuckImplementation::EndLoop(const std::string& source, std::size_t& index, std::size_t prevIndex)
{
    throw BrainfuckInterpreter::Error{ "Found ending bracket alone!", prevIndex + index };
}
