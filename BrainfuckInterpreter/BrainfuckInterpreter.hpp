#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "UCException.hpp"

#define NODISCARD(Message) [[nodiscard(Message)]]
#define NODISCARD_BF_RESULT() NODISCARD("Returns brainfuck interpretation result!")

class BrainfuckIntrepreter
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
    BrainfuckIntrepreter(size_t memorySize = 30000u);
    ~BrainfuckIntrepreter();

    NODISCARD_BF_RESULT()
    std::string InterpretSection(const std::string& tokens, size_t start = 0u);

    NODISCARD_BF_RESULT()
    std::string InterpretFile(const std::string& filepath);

private:
    unsigned char* m_Memory  = nullptr;
    unsigned char* m_Pointer = nullptr;
};
