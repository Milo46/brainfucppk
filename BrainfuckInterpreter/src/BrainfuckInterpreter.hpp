#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "UCException.hpp"
#include "BrainfuckAttributes.hpp"

class BrainfuckInterpreter
{
public:
    class Error : public UCException
    {
    public:
        Error(const char* message, size_t tokenIndex);
        size_t GetTokenIndex() const;

    private:
        size_t m_TokenIndex;
    };

public:
    BrainfuckInterpreter(size_t memorySize = 30000u);
    ~BrainfuckInterpreter();

    BRAINFUCK_NODISCARD_RESULT()
    std::string InterpretSection(const std::string& tokens, size_t start = 0u);

    BRAINFUCK_NODISCARD_RESULT()
    std::string InterpretFile(const std::string& filepath);

private:
    unsigned char* m_Memory  = nullptr;
    unsigned char* m_Pointer = nullptr;
};
