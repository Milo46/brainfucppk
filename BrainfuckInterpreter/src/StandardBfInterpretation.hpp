#pragma once

#include "BfImplementation.hpp"
#include "BfInterpreter.hpp"

class StandardBrainfuckImplementation : public BrainfuckImplementation
{
public:
    StandardBrainfuckImplementation(BrainfuckInterpreter* interpreter);

public:
    virtual void IncrementPointer(const std::string& source, std::size_t& index) override;
    virtual void DecrementPointer(const std::string& source, std::size_t& index) override;
    virtual void IncrementValue(const std::string& source, std::size_t& index) override;
    virtual void DecrementValue(const std::string& source, std::size_t& index) override;
    virtual void Write(const std::string& source, std::size_t& index) override;
    virtual void Read(const std::string& source, std::size_t& index) override;
    virtual void BeginLoop(const std::string& source, std::size_t& index, std::size_t prevIndex) override;
    virtual void EndLoop(const std::string& source, std::size_t& index, std::size_t prevIndex) override;
};
