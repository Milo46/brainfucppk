#pragma once

#include "core/BfImplementation.hpp"

#include <map>

enum class StandardBrainfuckToken : char
{
    IncrementPointer = '>',
    DecrementPointer = '<',
    IncrementValue   = '+',
    DecrementValue   = '-',
    Write            = '.',
    Read             = ',',
    BeginLoop        = '[',
    EndLoop          = ']',

    End,
};

class StandardBrainfuckImplementation : public BrainfuckImplementation
{
public:
    explicit StandardBrainfuckImplementation(unsigned char* pointer);

protected:
    virtual bool ResolveToken(const FileData& sourceData, std::size_t& index) override;

private:
    void IncrementPointer(const FileData& sourceData, std::size_t& index);
    void DecrementPointer(const FileData& sourceData, std::size_t& index);
    void IncrementValue(const FileData& sourceData, std::size_t& index);
    void DecrementValue(const FileData& sourceData, std::size_t& index);
    void Write(const FileData& sourceData, std::size_t& index);
    void Read(const FileData& sourceData, std::size_t& index);
    void BeginLoop(const FileData& sourceData, std::size_t& index);
    void EndLoop(const FileData& sourceData, std::size_t& index);

private:
    std::map<std::size_t, std::size_t> m_LoopsPositions;
};
