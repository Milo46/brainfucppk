#pragma once

#include <optional>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "BfImplementation.hpp"

#include "utility/Noncopyable.hpp"

class BrainfuckInterpreter : private NonCopyable<BrainfuckInterpreter>
{
public:
    /* Special token which ends interpreting a file when thrown */
    struct EndProgram {};

public:
    explicit BrainfuckInterpreter(uint32_t memorySize);
    ~BrainfuckInterpreter();

    void InterpretFile(const std::string& filepath);
    void ExecuteProject(const std::string& filepath);

private:
    void ResetEnvironment();

private:
    BrainfuckImplementation* m_Implementation{ nullptr };

    unsigned char* m_Memory{ nullptr };
    unsigned char* m_Pointer{ nullptr };

    uint32_t m_MemorySize;

    std::string m_Output;
};
