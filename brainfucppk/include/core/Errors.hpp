#pragma once

#include "Config.hpp"

#include <iostream>
#include <string>

BRAINFUCPPK_BEGIN

/**
 * @brief Brainfuck error, base class of all brainfuck errrors.
 */
class Error : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return m_Storage.what();
    }

protected:
    Error(const std::string& message)
        : ::std::exception{}, m_Storage{ message } {}

protected:
    static std::string Name(const std::string& name);

private:
    std::runtime_error m_Storage;
};

/**
 * @brief Brainfuck basic error class, used for
 *  basic, strictly uncategorized errors.
 */
class BasicError : public Error
{
public:
    inline static const std::string c_Name = "basic_error";

public:
    static BasicError Create(const std::string& details);

private:
    BasicError(const std::string& whatArg);
};

/**
 * @brief Brainfuck file error class, used for
 *  describing all kind of errors associated with files.
 */
class FileError : public Error
{
public:
    inline static const std::string c_Name = "file_error";

public:
    static FileError Create(const std::string& sourceFilepath, const std::string& details);

private:
    FileError(const std::string& whatArg);
};

/**
 * @brief Brainfuck interpreter error class, used for
 *  describing all kind of errors which occur during source interpretation.
 */
class InterpreterError : public Error
{
public:
    inline static const std::string c_Name = "interpreter_error";

public:
    static InterpreterError Create(const std::string& sourceFilepath, std::size_t position, const std::string& details);

private:
    InterpreterError(const std::string& whatArg);
};

BRAINFUCPPK_END
