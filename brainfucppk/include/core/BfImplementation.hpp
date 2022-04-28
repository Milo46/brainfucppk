#pragma once

#include <functional>
#include <string>
#include <map>

#include "utility/FileData.hpp"

class BrainfuckInterpreter;
class BrainfuckImplementation;

/**
 * #TODO: ugly and not dynamic, come up with a better idea of storing implementations.
 */
enum class BFImplementationEnum
{
    Standard,
    Extended1,
    Extended2,
    Extended3,
};

BFImplementationEnum GetBrainfuckImplementationFromString(const std::string& name);

BrainfuckImplementation* GetBrainfuckImplementation(const std::string& name, unsigned char* pointer);
BrainfuckImplementation* GetBrainfuckImplementation(BFImplementationEnum implementation, unsigned char* pointer);

/**
 * @brief base brainfuck implementation class,
 *        describes necessary behaviour for every implementation.
 */
class BrainfuckImplementation
{
public:
    BrainfuckImplementation(unsigned char* pointer);

public:
    /**
     * @brief Returns false if token has not been resolved.
     * 
     * @param source source code of brainfuck.
     * @param index index of which token to resolve.
     * @return true if the token has been resolved and false otherwise.
     */
    virtual bool ResolveToken(const FileData& sourceData, std::size_t& index) = 0;

protected:
    unsigned char* p_Pointer{ nullptr };
};
