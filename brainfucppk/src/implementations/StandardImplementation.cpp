#include "implementations/StandardImplementation.hpp"

#include "core/Interpreter.hpp"
#include "core/Errors.hpp"

#include <iostream>

BRAINFUCPPK_BEGIN

namespace _Internal
{
    std::size_t FindClosingBracket(const std::string& source, std::size_t start)
    {
        std::size_t bracketLevel = 0u;

        for (std::size_t i = start; i < source.size(); ++i)
        {
            switch (source[i])
            {
            case static_cast<char>(StandardToken::BeginLoop): ++bracketLevel; break;
            case static_cast<char>(StandardToken::EndLoop): if (!(--bracketLevel)) return i; break;

            default: break;
            }
        }

        return static_cast<std::size_t>(-1);
    }
}

StandardImplementation::StandardImplementation(const WarpableIterator<unsigned char>& pointer, std::ostream& output, std::istream& input)
    : Implementation(pointer, output, input), m_LoopsPositions() {}

bool StandardImplementation::ResolveToken(const std::string& source, std::size_t& index)
{
    switch (source[index])
    {
    case static_cast<char>(StandardToken::IncrementPointer): IncrementPointer(source, index); break;
    case static_cast<char>(StandardToken::DecrementPointer): DecrementPointer(source, index); break;
    case static_cast<char>(StandardToken::IncrementValue):   IncrementValue(source, index);   break;
    case static_cast<char>(StandardToken::DecrementValue):   DecrementValue(source, index);   break;
    case static_cast<char>(StandardToken::Write):            Write(source, index);            break;
    case static_cast<char>(StandardToken::Read):             Read(source, index);             break;
    case static_cast<char>(StandardToken::BeginLoop):        BeginLoop(source, index);        break;
    case static_cast<char>(StandardToken::EndLoop):          EndLoop(source, index);          break;

    default: return false;
    }

    return true;
}

void StandardImplementation::IncrementPointer(const std::string& source, std::size_t& index) { ++p_Pointer; }
void StandardImplementation::DecrementPointer(const std::string& source, std::size_t& index) { --p_Pointer; }
void StandardImplementation::IncrementValue(const std::string& source, std::size_t& index) { ++(*p_Pointer); }
void StandardImplementation::DecrementValue(const std::string& source, std::size_t& index) { --(*p_Pointer); }

void StandardImplementation::Write(const std::string& source, std::size_t& index) { p_OutputStream << *p_Pointer; }
void StandardImplementation::Read(const std::string& source, std::size_t& index)  { p_InputStream  >> *p_Pointer; }

void StandardImplementation::BeginLoop(const std::string& source, std::size_t& index)
{
    if (m_LoopsPositions.find(index) == m_LoopsPositions.end())
    {
        auto pos = _Internal::FindClosingBracket(source, index);

        if (pos == static_cast<std::size_t>(-1))
            throw InterpreterError::Create(source, index, "failed to find ending bracket!");

        m_LoopsPositions.insert(std::make_pair(index, pos));
    }

    if (!(*p_Pointer))
    {
        auto openingBracketPos = index;
        index = m_LoopsPositions[index];
        m_LoopsPositions.erase(openingBracketPos);
    }
}

void StandardImplementation::EndLoop(const std::string& source, std::size_t& index)
{
    for (const auto& it : m_LoopsPositions) if (it.second == index)
    {
        //
        // Why is there `it.first - 1u`?
        // Because in every interpreter executaion iteration index is being
        // incremented by one and we need to get to the BeginLoop() method
        // in order to check the loop's expression.
        // 
        // I just need that explanation if I ever forget it.
        //

        index = it.first - 1u;
        return;
    }

    throw InterpreterError::Create(source, index, "found ending bracket alone!");
}

BRAINFUCPPK_END
