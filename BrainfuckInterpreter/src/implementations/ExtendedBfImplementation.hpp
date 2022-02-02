#pragma once

#include "StandardBfImplementation.hpp"

class ExtendedBrainfuckImplementation : public StandardBrainfuckImplementation
{
public:
    ExtendedBrainfuckImplementation(unsigned char* pointer);

protected:
    virtual bool ResolveToken(const std::string& source, std::size_t& index) override;
};
