#pragma once

///
/// Exceptions handlers
///

#define HANDLE_BRAINFUCK_EXCEPTION(Exception) \
    std::cerr << "Brainfuck interpreter exception has occurred: \n" \
        "\tMessage: "  << Exception.What()          << "\n" \
        "\tPosition: " << Exception.GetTokenIndex() << "\n"

#define HANDLE_STANDARD_EXCEPTION(Exception) \
    std::cerr << "An exception has occurred: " << Exception.what() << '\n'

#define HANDLE_UNKNOWN_EXCEPTION() \
    std::cerr << "Something went really wrong, unhandled exception has been thrown!\n"

///
/// Exceptions catch blocks
///

#define CATCH_BLOCK(ExceptionType, ExceptionName, ExceptionHandler) \
    catch (ExceptionType ExceptionName) { \
        ExceptionHandler(ExceptionName); \
    }

#define CATCH_BLOCK_BRAINFUCK_EXCEPTION() \
    CATCH_BLOCK(BrainfuckInterpreter::Error&, e, HANDLE_BRAINFUCK_EXCEPTION)

#define CATCH_BLOCK_STANDARD_EXCEPTION() \
    CATCH_BLOCK(std::exception&, e, HANDLE_STANDARD_EXCEPTION)

#define CATCH_BLOCK_UNKNOWN_EXCEPTION() \
    CATCH_BLOCK(...,, HANDLE_UNKNOWN_EXCEPTION);
