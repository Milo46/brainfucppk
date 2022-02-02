#pragma once

#include "core/BfImplementation.hpp"
#include "core/BfInterpreter.hpp"

#include <map>

class StandardBrainfuckImplementation : public BrainfuckImplementation
{
public:
    StandardBrainfuckImplementation(unsigned char* pointer);

protected:
    virtual void ResolveToken(const std::string& source, std::size_t& index) override;

private:
    void IncrementPointer(const std::string& source, std::size_t& index);
    void DecrementPointer(const std::string& source, std::size_t& index);
    void IncrementValue(const std::string& source, std::size_t& index);
    void DecrementValue(const std::string& source, std::size_t& index);
    void Write(const std::string& source, std::size_t& index);
    void Read(const std::string& source, std::size_t& index);
    void BeginLoop(const std::string& source, std::size_t& index);
    void EndLoop(const std::string& source, std::size_t& index);

private:
    std::map<std::size_t, std::size_t> m_LoopsPositions;
};
