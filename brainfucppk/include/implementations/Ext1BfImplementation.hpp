#pragma once

#include "StandardBfImplementation.hpp"

enum class Ext1BrainfuckToken : char
{
    Begin = static_cast<char>(StandardBrainfuckToken::End),

    EndProgram        = '@',
    SetStorage        = '$',
    GetStorage        = '!',
    RightLogicalShift = '}',
    LeftLogicalShift  = '{',
    BitwiseNot        = '~',
    BitwiseXor        = '^',
    BitwiseAnd        = '&',
    BitwiseOr         = '|',

    End,
};

class Ext1BrainfuckImplementation : public StandardBrainfuckImplementation
{
public:
    explicit Ext1BrainfuckImplementation(unsigned char* pointer);

protected:
    virtual bool ResolveToken(const FileData& source, std::size_t& index) override;

private:
    void EndProgram(const FileData& source, std::size_t& index);
    void SetStorage(const FileData& source, std::size_t& index);
    void GetStorage(const FileData& source, std::size_t& index);
    void RightLogicalShift(const FileData& source, std::size_t& index);
    void LeftLogicalShift(const FileData& source, std::size_t& index);
    void BitwiseNot(const FileData& source, std::size_t& index);
    void BitwiseXor(const FileData& source, std::size_t& index);
    void BitwiseAnd(const FileData& source, std::size_t& index);
    void BitwiseOr(const FileData& source, std::size_t& index);

private:
    unsigned char m_Storage = 0u;
};
