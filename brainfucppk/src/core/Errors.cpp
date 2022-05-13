#include "core/Errors.hpp"

BRAINFUCPPK_BEGIN

std::string Error::Name(const std::string& name)
{
    return "[brainfuck.exception." + name + "] ";
}

BasicError BasicError::Create(
    const std::string& details
)
{
    return { Error::Name(c_Name) + "basic error: " + details };
}

BasicError::BasicError(const std::string& whatArg)
    : Error{ whatArg } {}

FileError FileError::Create(
    const std::string& sourceFilepath,
    const std::string& details
)
{
    return { Error::Name(c_Name) + "file error [" + sourceFilepath + "]: " + details };
}

FileError::FileError(const std::string& whatArg)
        : Error{ whatArg } {}

InterpreterError InterpreterError::Create(
    const std::string& sourceFilepath,
    std::size_t position,
    const std::string& details
)
{
    return { Error::Name(c_Name) + "interpretation error [" + sourceFilepath + ":" + std::to_string(position) + "]: " + details };
}

InterpreterError::InterpreterError(const std::string& whatArg)
        : Error{ whatArg } {}

BRAINFUCPPK_END
