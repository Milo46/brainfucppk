/*
    OPTIONS FOR BRAINFUCK INTERPRETER:
        - [optional] CONNECT_MEMORY_ENDS - if the memory pointer goes below 0 or over the max value, it is being looped
        - [optional] CUSTOM_MEMORY_SIZE [for small sizes, better use CONNECT_MEMORY_ENDS] - sets custom size of memory

        - HOW TO PRINT DATA ( methods )
        - HOW TO READ DATA  ( methods )

        // Example
        bfinterpreter.exe -memory_size 40000 -connect_memory_ends

    TODO:
        - Detect infinite loops! //auto result = bfInterpreter.InterpretSection("++[><]", 0u);
*/

#include <iostream>

#include <nlohmann/json.hpp>
#include "core/BfInterpreter.hpp"

int main(int argc, char** argv)
{
    try
    {
        BrainfuckInterpreter interpreter{ 30'000u };
        interpreter.ExecuteProject("resources/scripts/hello_world.json");

        return EXIT_SUCCESS;
    }
    catch (BrainfuckInterpreter::Error& e)
    {
        std::cerr << "Brainfuck interpreter exception has occurred: \n"
            "\tMessage: "  << e.what()          << "\n"
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

    return EXIT_FAILURE;
}
