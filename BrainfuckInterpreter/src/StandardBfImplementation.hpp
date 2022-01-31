#pragma once

#include "BfImplementation.hpp"
#include "BfInterpreter.hpp"

#include <map>

class StandardBrainfuckImplementation : public BrainfuckImplementation
{
public:
    StandardBrainfuckImplementation(unsigned char* pointer);

public:
    virtual void IncrementPointer(const std::string& source, std::size_t& index) override;
    virtual void DecrementPointer(const std::string& source, std::size_t& index) override;
    virtual void IncrementValue(const std::string& source, std::size_t& index) override;
    virtual void DecrementValue(const std::string& source, std::size_t& index) override;
    virtual void Write(const std::string& source, std::size_t& index) override;
    virtual void Read(const std::string& source, std::size_t& index) override;
    virtual void BeginLoop(const std::string& source, std::size_t& index) override;
    virtual void EndLoop(const std::string& source, std::size_t& index) override;

private:
    std::map<std::size_t, std::size_t> m_LoopsPositions;
};
