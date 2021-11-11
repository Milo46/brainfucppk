/*
    OPTIONS FOR BRAINFUCK INTERPRETER:
        - [optional] CONNECT_MEMORY_ENDS - if the memory pointer goes below 0 or over the max value, it is being looped
        - [optional] CUSTOM_MEMORY_SIZE [for small sizes, better use CONNECT_MEMORY_ENDS] - sets custom size of memory

        // Example
        bfinterpreter.exe -memory_size 40000 -connect_memory_ends

    TODO:
        - Detect infinite loops! //auto result = bfInterpreter.InterpretSection("++[><]", 0u);
*/

#include <iostream>
#include <vector>
#include <string>

#include "BrainfuckInterpreter.hpp"
#include "ExceptionHandlers.hpp"

int main(size_t argc, char** argv)
{
    try
    {
        BrainfuckInterpreter bfInterpreter = { 30000u };
        std::cout << bfInterpreter.InterpretFile("resources/hello_world.bf") << '\n';

        return EXIT_SUCCESS;
    }
    catch (BrainfuckInterpreter::Error& e)
    {
        std::cerr << "Brainfuck interpreter exception has occurred: \n"
            "\tMessage: "  << e.What()          << "\n"
            "\tPosition: " << e.GetTokenIndex() << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "An exception has occurred: " << e.what() << '\n';
    }
    catch (...)
    {
        std::cerr << "Something went really wrong, unhandled exception has been thrown!\n";
    }

    /*CATCH_BLOCK_BRAINFUCK_EXCEPTION()
    CATCH_BLOCK_STANDARD_EXCEPTION()
    CATCH_BLOCK_UNKNOWN_EXCEPTION()*/

    return EXIT_FAILURE;
}
