#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "BfImplementation.hpp"

class BrainfuckInterpreter
{
public:
    class Error : public std::exception
    {
    public:
        Error(const char* message, std::size_t tokenIndex);
        std::size_t GetTokenIndex() const;

    private:
        std::size_t m_TokenIndex;
    };

public:
    friend BrainfuckImplementation;

public:
    BrainfuckInterpreter();
    ~BrainfuckInterpreter();

    void InterpretSection(const std::string& source, size_t prevIndex = 0u);
    void InterpretFile(const std::string& filepath);

private:
    BrainfuckImplementation* m_Implementation = nullptr;

    unsigned char* m_Memory  = nullptr;
    unsigned char* m_Pointer = nullptr;
};