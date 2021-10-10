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
#include <string>

#include "BrainfuckInterpreter.hpp"

int main(size_t argc, char** argv) 
{
    try
    {
        BrainfuckIntrepreter bfInterpreter = { 30000u };
        std::cout << bfInterpreter.InterpretFile("resources/hello_world.bf") << '\n';
    }
    catch (BrainfuckIntrepreter::Error& e)
    {
        std::cerr << "Brainfuck interpreter exception has occurred: \n"
            "\tMessage: "  << e.What()          << "\n"
            "\tPosition: " << e.GetTokenIndex() << "\n";

        return EXIT_FAILURE;
    }
    catch (std::exception& e)
    {
        std::cerr << "An exception has occurred: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Something went really wrong, unhandled exception has been thrown!\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
