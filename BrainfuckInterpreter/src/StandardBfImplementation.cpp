#include "StandardBfImplementation.hpp"

#include <iostream>

static std::size_t FindClosingBracket(const std::string& source, std::size_t start)
{
    std::size_t bracketLevel = 0u;

    for (std::size_t i = start; i < source.size(); ++i)
    {
        switch (source[i])
        {
        case BrainfuckToken::BeginLoop: ++bracketLevel; break;
        case BrainfuckToken::EndLoop: if (!(--bracketLevel)) return i; break;

        default: break;
        }
    }

    return static_cast<std::size_t>(-1);
}

StandardBrainfuckImplementation::StandardBrainfuckImplementation(unsigned char* pointer)
    : BrainfuckImplementation(pointer), m_LoopsPositions() {}

void StandardBrainfuckImplementation::IncrementPointer(const std::string& source, std::size_t& index) { ++p_Pointer; }
void StandardBrainfuckImplementation::DecrementPointer(const std::string& source, std::size_t& index) { --p_Pointer; }
void StandardBrainfuckImplementation::IncrementValue(const std::string& source, std::size_t& index) { ++(*p_Pointer); }
void StandardBrainfuckImplementation::DecrementValue(const std::string& source, std::size_t& index) { --(*p_Pointer); }

void StandardBrainfuckImplementation::Write(const std::string& source, std::size_t& index) { std::cout << *p_Pointer; }
void StandardBrainfuckImplementation::Read(const std::string& source, std::size_t& index) { std::cin >> *p_Pointer; }

void StandardBrainfuckImplementation::BeginLoop(const std::string& source, std::size_t& index)
{
    if (m_LoopsPositions.find(index) == m_LoopsPositions.end())
    {
        auto pos = FindClosingBracket(source, index);

        if (pos == static_cast<std::size_t>(-1))
            throw BrainfuckInterpreter::Error{ "Failed to find ending bracket!", index };

        m_LoopsPositions.insert(std::make_pair(index, pos));
    }

    if (!(*p_Pointer))
    {
        auto openingBracketPos = index;
        index = m_LoopsPositions[index];
        m_LoopsPositions.erase(openingBracketPos);
    }
}

void StandardBrainfuckImplementation::EndLoop(const std::string& source, std::size_t& index)
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

    throw BrainfuckInterpreter::Error{ "Found ending bracket alone!", index };
}
