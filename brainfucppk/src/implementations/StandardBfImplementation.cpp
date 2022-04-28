#include "implementations/StandardBfImplementation.hpp"

#include "core/BfInterpreter.hpp"
#include "core/BfErrors.hpp"

#include <iostream>

namespace _Internal
{
    std::size_t FindClosingBracket(const FileData& sourceData, std::size_t start)
    {
        const auto& source = sourceData.GetSource();

        std::size_t bracketLevel = 0u;

        for (std::size_t i = start; i < source.size(); ++i)
        {
            switch (source[i])
            {
            case static_cast<char>(StandardBrainfuckToken::BeginLoop): ++bracketLevel; break;
            case static_cast<char>(StandardBrainfuckToken::EndLoop): if (!(--bracketLevel)) return i; break;

            default: break;
            }
        }

        return static_cast<std::size_t>(-1);
    }
}

StandardBrainfuckImplementation::StandardBrainfuckImplementation(unsigned char* pointer)
    : BrainfuckImplementation(pointer), m_LoopsPositions() {}

bool StandardBrainfuckImplementation::ResolveToken(const FileData& sourceData, std::size_t& index)
{
    switch (sourceData.GetSource()[index])
    {
    case static_cast<char>(StandardBrainfuckToken::IncrementPointer): IncrementPointer(sourceData, index); break;
    case static_cast<char>(StandardBrainfuckToken::DecrementPointer): DecrementPointer(sourceData, index); break;
    case static_cast<char>(StandardBrainfuckToken::IncrementValue):   IncrementValue(sourceData, index);   break;
    case static_cast<char>(StandardBrainfuckToken::DecrementValue):   DecrementValue(sourceData, index);   break;
    case static_cast<char>(StandardBrainfuckToken::Write):            Write(sourceData, index);            break;
    case static_cast<char>(StandardBrainfuckToken::Read):             Read(sourceData, index);             break;
    case static_cast<char>(StandardBrainfuckToken::BeginLoop):        BeginLoop(sourceData, index);        break;
    case static_cast<char>(StandardBrainfuckToken::EndLoop):          EndLoop(sourceData, index);          break;

    default: return false;
    }

    return true;
}

void StandardBrainfuckImplementation::IncrementPointer(const FileData& sourceData, std::size_t& index) { ++p_Pointer; }
void StandardBrainfuckImplementation::DecrementPointer(const FileData& sourceData, std::size_t& index) { --p_Pointer; }
void StandardBrainfuckImplementation::IncrementValue(const FileData& sourceData, std::size_t& index) { ++(*p_Pointer); }
void StandardBrainfuckImplementation::DecrementValue(const FileData& sourceData, std::size_t& index) { --(*p_Pointer); }

void StandardBrainfuckImplementation::Write(const FileData& sourceData, std::size_t& index) { std::cout << *p_Pointer; }
void StandardBrainfuckImplementation::Read(const FileData& sourceData, std::size_t& index) { std::cin >> *p_Pointer; }

void StandardBrainfuckImplementation::BeginLoop(const FileData& sourceData, std::size_t& index)
{
    if (m_LoopsPositions.find(index) == m_LoopsPositions.end())
    {
        auto pos = _Internal::FindClosingBracket(sourceData, index);

        if (pos == static_cast<std::size_t>(-1))
            throw BrainfuckInterpreterError::Create(sourceData.GetFilepath(), index, "failed to find ending bracket!");

        m_LoopsPositions.insert(std::make_pair(index, pos));
    }

    if (!(*p_Pointer))
    {
        auto openingBracketPos = index;
        index = m_LoopsPositions[index];
        m_LoopsPositions.erase(openingBracketPos);
    }
}

void StandardBrainfuckImplementation::EndLoop(const FileData& sourceData, std::size_t& index)
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

    throw BrainfuckInterpreterError::Create(sourceData.GetFilepath(), index, "found edning bracket alone!");
}
