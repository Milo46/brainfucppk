/*
    OPTIONS FOR BRAINFUCK INTERPRETER:
        - [optional] CONNECT_MEMORY_ENDS - if the memory pointer goes below 0 or over the max value, it is being looped
        - [optional] CUSTOM_MEMORY_SIZE [for small sizes, better use CONNECT_MEMORY_ENDS] - sets custom size of memory

        // Example
        bfinterpreter.exe -memory_size 40000

    TODO:
        - Detect infinite loops! //auto result = bfInterpreter.InterpretSection("++[><]", 0u);
*/

/*
    New application:
        - arguments parser (interpret single file or entire project)
            * brainfuccpk.exe --file example.bf
            * brainfuccpk.exe --project example.json
        
        brainfuccpk --project scripts/hello_world.json
        brainfuccpk --file example.bf --memory 40000
*/

#include <iostream>
#include <fstream>

#include "core/Interpreter.hpp"
#include "core/Errors.hpp"

#include "ProjectInterpreter.hpp"

int main(int argc, char** argv)
{
    std::cout << "Input filepath: ";

    std::string filepath{};
    std::cin >> filepath;

    try
    {
        ProjectInterpreter interpreter{ 30'000u };
        interpreter.InterpretProject(filepath);
    }
    catch (Brainfucppk::Error& e)
    {
        std::cout << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
