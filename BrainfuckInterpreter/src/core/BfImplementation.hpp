#pragma once

#include "core/BfTokens.hpp"

#include <functional>
#include <string>
#include <map>

class BrainfuckInterpreter;
class BrainfuckImplementation;

enum class BrainfuckImplementationEnum
{
    Standard,
    Extended,
};

BrainfuckImplementationEnum GetBrainfuckImplementationFromString(const std::string& name);
BrainfuckImplementation* GetBrainfuckImplementation(const std::string& name, unsigned char* pointer);
BrainfuckImplementation* GetBrainfuckImplementation(BrainfuckImplementationEnum implementation, unsigned char* pointer);

class BrainfuckImplementation
{
public:
    BrainfuckImplementation(unsigned char* pointer);

public:
    virtual void ResolveToken(const std::string& source, std::size_t& index) = 0;

protected:
    unsigned char* p_Pointer;
};
