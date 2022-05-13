#pragma once

#include "StandardImplementation.hpp"

BRAINFUCPPK_BEGIN

enum class Ext1Token : char
{
    Begin = static_cast<char>(StandardToken::End),

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

class Ext1Implementation : public StandardImplementation
{
public:
    Ext1Implementation(const WarpableIterator<unsigned char>& pointer, std::ostream& output, std::istream& input);

protected:
    virtual bool ResolveToken(const std::string& source, std::size_t& index) noexcept(false) override;

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

BRAINFUCPPK_END
