#pragma once

#include "core/BfTokens.hpp"

#include <functional>
#include <string>
#include <map>

#define BF_BIND(_MethodName) \
    std::bind(&_MethodName, this, std::placeholders::_1, std::placeholders::_2)

class BrainfuckInterpreter;
class BrainfuckImplementation;

BrainfuckImplementation* GetBrainfuckImplementation(unsigned char* pointer);
BrainfuckImplementation* GetBrainfuckImplementation(const std::string& name, unsigned char* pointer);

// Implement: LoadTokens(jsonFile) + VerifyTokens(tokens)
class BrainfuckImplementation
{
public:
    using TokenCallback = std::function<void(const std::string&, std::size_t&)>;

public:
    BrainfuckImplementation(unsigned char* pointer);
    virtual ~BrainfuckImplementation() = default;

    void InterpretTokens(const std::string& source);

protected:
    virtual TokenCallback ResolveToken(char token) = 0;

protected:
    unsigned char* p_Pointer;
};
