#pragma once

#include <stdint.h>

enum class BrainfuckAPI { Standard };

class BrainfuckConfiguration
{
public:
    BrainfuckConfiguration()  = delete;
    ~BrainfuckConfiguration() = delete;

public:
    inline static BrainfuckAPI GetBrainfuckAPI() { return s_BrainfuckAPI; }
    inline static uint32_t GetMemorySize()       { return s_MemorySize; }

private:
    static BrainfuckAPI s_BrainfuckAPI;
    static uint32_t s_MemorySize;
};
