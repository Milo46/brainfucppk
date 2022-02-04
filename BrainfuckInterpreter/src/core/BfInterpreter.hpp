#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "BfImplementation.hpp"

#include "utility/Noncopyable.hpp"

class BrainfuckInterpreter : private NonCopyable<BrainfuckInterpreter>
{
public:
    struct EndProgram {};

    class Error : public std::exception
    {
    public:
        Error(const char* message, std::size_t tokenIndex);
        std::size_t GetTokenIndex() const;

    private:
        std::size_t m_TokenIndex;
    };

public:
    explicit BrainfuckInterpreter(uint32_t memorySize);
    ~BrainfuckInterpreter();

    void InterpretFile(const std::string& filepath);
    void ExecuteProject(const std::string& filepath);

private:
    void ResetEnvironment();

private:
    BrainfuckImplementation* m_Implementation = nullptr;

    unsigned char* m_Memory  = nullptr;
    unsigned char* m_Pointer = nullptr;

    uint32_t m_MemorySize;
    std::string m_Output;
};
