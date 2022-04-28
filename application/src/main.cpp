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

/*
    New application:
        - arguments parser (interpret single file or entire project)
            * brainfuccpk.exe --file example.bf
            * brainfuccpk.exe --project example.json
*/

// todo: new error system, check experimental project on your disk!

#include <iostream>

#include "core/BfInterpreter.hpp"
#include "core/BfErrors.hpp"

int main(int argc, char** argv)
{
    std::string projectFilepath{};

    std::cout << "Type in json project filepath: ";
    std::cin >> projectFilepath;

    try
    {
        BrainfuckInterpreter interpreter{ 30'000u };
        interpreter.ExecuteProject(projectFilepath);
    }
    catch (BrainfuckError& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (std::runtime_error& e)
    {
        
    }

    return EXIT_SUCCESS;
}
