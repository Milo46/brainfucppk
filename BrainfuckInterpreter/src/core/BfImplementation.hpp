#pragma once

#include "core/BfTokens.hpp"

#include <functional>
#include <string>
#include <map>

class BrainfuckInterpreter;
class BrainfuckImplementation;

enum class BFImplementationEnum
{
    Standard,
    Extended1,
    Extended2,
    Extended3,
};

BFImplementationEnum GetBrainfuckImplementationFromString(const std::string& name);
BrainfuckImplementation* GetBrainfuckImplementation(const std::string& name, unsigned char* pointer);
BrainfuckImplementation* GetBrainfuckImplementation(BFImplementationEnum implementation, unsigned char* pointer);

class BrainfuckImplementation
{
public:
    BrainfuckImplementation(unsigned char* pointer);

public:
    // Returns false if token has not been resolved!
    virtual bool ResolveToken(const std::string& source, std::size_t& index) = 0;

protected:
    unsigned char* p_Pointer;
};
