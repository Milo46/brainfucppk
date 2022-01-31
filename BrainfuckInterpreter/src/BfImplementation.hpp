#pragma once

#include "BfTokens.hpp"

#include <string>
#include <map>

class BrainfuckInterpreter;
class BrainfuckImplementation;

BrainfuckImplementation* GetBrainfuckImplementation(unsigned char* pointer);

// Implement: LoadTokens(jsonFile) + VerifyTokens(tokens)
class BrainfuckImplementation
{
public:
    BrainfuckImplementation(unsigned char* pointer);
    virtual ~BrainfuckImplementation() = default;

public:
    virtual void IncrementPointer(const std::string& source, std::size_t& index) = 0;
    virtual void DecrementPointer(const std::string& source, std::size_t& index) = 0;
    virtual void IncrementValue(const std::string& source, std::size_t& index) = 0;
    virtual void DecrementValue(const std::string& source, std::size_t& index) = 0;
    virtual void Write(const std::string& source, std::size_t& index) = 0;
    virtual void Read(const std::string& source, std::size_t& index) = 0;
    virtual void BeginLoop(const std::string& source, std::size_t& index) = 0;
    virtual void EndLoop(const std::string& source, std::size_t& index) = 0;

protected:
    unsigned char* p_Pointer;

private:
    std::map<std::string, unsigned char> m_Tokens;
};
