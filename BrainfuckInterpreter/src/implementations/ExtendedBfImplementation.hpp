#pragma once

#include "StandardBfImplementation.hpp"

enum class ExtendedBrainfuckToken : char
{
    Begin = static_cast<char>(StandardBrainfuckToken::End),

    _Token1 = '@',
    _Token2 = '$',
    _Token3 = '!',
    _token4 = '}',
    _Token5 = '{',
    _Token6 = '~',
    _Token7 = '^',
    _Token8 = '&',
    _Token9 = '|',

    End,
};

class ExtendedBrainfuckImplementation : public StandardBrainfuckImplementation
{
public:
    ExtendedBrainfuckImplementation(unsigned char* pointer);

protected:
    virtual bool ResolveToken(const std::string& source, std::size_t& index) override;
};
