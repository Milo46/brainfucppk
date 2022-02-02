#pragma once

#include "StandardBfImplementation.hpp"

enum class ExtendedBrainfuckToken : char
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

class ExtendedBrainfuckImplementation : public StandardBrainfuckImplementation
{
public:
    ExtendedBrainfuckImplementation(unsigned char* pointer);

protected:
    virtual bool ResolveToken(const std::string& source, std::size_t& index) override;

private:
    void EndProgram(const std::string& source, std::size_t& index);
    void SetStorage(const std::string& source, std::size_t& index);
    void GetStorage(const std::string& source, std::size_t& index);
    void RightLogicalShift(const std::string& source, std::size_t& index);
    void LeftLogicalShift(const std::string& source, std::size_t& index);
    void BitwiseNot(const std::string& source, std::size_t& index);
    void BitwiseXor(const std::string& source, std::size_t& index);
    void BitwiseAnd(const std::string& source, std::size_t& index);
    void BitwiseOr(const std::string& source, std::size_t& index);

private:
    unsigned char m_Storage = 0u;
};
