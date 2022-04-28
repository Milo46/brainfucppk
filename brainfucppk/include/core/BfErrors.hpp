#pragma once

#include <iostream>
#include <string>

#define DECLARE_BRAINFUCK_ERROR(_Name, _ExceptionName)           \
    class _Name : public BfException                             \
    {                                                            \
    public:                                                      \
        inline static const std::string c_Name = _ExceptionName; \
                                                                 \
    public:                                                      \
        static _Name Create(const std::string& details);         \
                                                                 \
    private:                                                     \
        _Name(const std::string& whatArg);                       \
    }

/**
 * @brief Brainfuck error, base class of all brainfuck errrors.
 */
class BrainfuckError : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return m_Storage.what();
    }

protected:
    BrainfuckError(const std::string& message)
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
class BrainfuckBasicError : public BrainfuckError
{
public:
    inline static const std::string c_Name = "basic_error";

public:
    static BrainfuckBasicError Create(const std::string& details);

private:
    BrainfuckBasicError(const std::string& whatArg);
};

/**
 * @brief Brainfuck file error class, used for
 *  describing all kind of errors associated with files.
 */
class BrainfuckFileError : public BrainfuckError
{
public:
    inline static const std::string c_Name = "file_error";

public:
    static BrainfuckFileError Create(const std::string& sourceFilepath, const std::string& details);

private:
    BrainfuckFileError(const std::string& whatArg);
};

/**
 * @brief Brainfuck interpreter error class, used for
 *  describing all kind of errors which occur during source interpretation.
 */
class BrainfuckInterpreterError : public BrainfuckError
{
public:
    inline static const std::string c_Name = "interpreter_error";

public:
    static BrainfuckInterpreterError Create(const std::string& sourceFilepath, std::size_t position, const std::string& details);

private:
    BrainfuckInterpreterError(const std::string& whatArg);
};
