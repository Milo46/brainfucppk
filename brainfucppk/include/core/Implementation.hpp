#pragma once

#include <functional>
#include <string>
#include <map>

#include "core/Config.hpp"
#include "utility/WarpableIterator.hpp"

BRAINFUCPPK_BEGIN

class Interpreter;
class Implementation;

/**
 * #TODO: ugly and not dynamic, come up with a better idea of storing implementations.
 */
enum class ImplementationEnum
{
    Standard,
    Extended1,
    Extended2,
    Extended3,
};

ImplementationEnum GetImplementationFromString(const std::string& name);

/**
 * @brief base brainfuck implementation class,
 *        describes necessary behaviour for every implementation.
 */
class Implementation
{
public:
    static Implementation* Create(Interpreter* owner, const std::string& name);
    static Implementation* Create(Interpreter* owner, ImplementationEnum implementation);

public:
    /**
     * @brief Returns false if token has not been resolved.
     * 
     * @param source source code of brainfuck.
     * @param index index of which token to resolve.
     * @return true if the token has been resolved and false otherwise.
     */
    virtual bool ResolveToken(const std::string& source, std::size_t& index) noexcept(false) = 0;

protected:
    Implementation(const WarpableIterator<unsigned char>& pointer, std::ostream& output, std::istream& input);

protected:
    WarpableIterator<unsigned char> p_Pointer;

    std::ostream& p_OutputStream;
    std::istream& p_InputStream;
};

BRAINFUCPPK_END
