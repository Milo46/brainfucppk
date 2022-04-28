#include "core/BfErrors.hpp"

std::string BrainfuckError::Name(const std::string& name)
{
    return "[brainfuck.exception." + name + "] ";
}

BrainfuckBasicError BrainfuckBasicError::Create(
    const std::string& details
)
{
    return { BrainfuckError::Name(c_Name) + "basic error: " + details };
}

BrainfuckBasicError::BrainfuckBasicError(const std::string& whatArg)
    : BrainfuckError{ whatArg } {}

BrainfuckFileError BrainfuckFileError::Create(
    const std::string& sourceFilepath,
    const std::string& details
)
{
    return { BrainfuckError::Name(c_Name) + "file error [" + sourceFilepath + "]: " + details };
}

BrainfuckFileError::BrainfuckFileError(const std::string& whatArg)
        : BrainfuckError{ whatArg } {}

BrainfuckInterpreterError BrainfuckInterpreterError::Create(
    const std::string& sourceFilepath,
    std::size_t position,
    const std::string& details
)
{
    return { BrainfuckError::Name(c_Name) + "interpretation error [" + sourceFilepath + ":" + std::to_string(position) + "]: " + details };
}

BrainfuckInterpreterError::BrainfuckInterpreterError(const std::string& whatArg)
        : BrainfuckError{ whatArg } {}
