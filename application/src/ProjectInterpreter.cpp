#include "ProjectInterpreter.hpp"
#include "BrainfuckProject.hpp"

#include "core/Errors.hpp"

#include <iostream>
#include <fstream>

namespace _Internal
{
    std::string ExportFileDirectory(const std::string& filepath)
    {
        return filepath.substr(0u, std::max(
            filepath.find_last_of('/')  + 1u,
            filepath.find_last_of('\\') + 1u
        ));
    }
}

ProjectInterpreter::ProjectInterpreter(const uint64_t memorySize)
    : Interpreter{ memorySize } {}

ProjectInterpreter::~ProjectInterpreter() {}

void ProjectInterpreter::InterpretProject(const std::string& filepath)
{
    BrainfuckProject project{};
    nlohmann::json jsonData{};

    try
    {
        std::ifstream file{ filepath };
        jsonData = nlohmann::json::parse(file);
    }
    catch (nlohmann::json::parse_error&)
    {
        throw Brainfucppk::FileError::Create(filepath, "failed to parse project file!");
    }

    if (!project.ParseJson(jsonData))
        throw Brainfucppk::BasicError::Create("ill-formed project's data!");
    
    std::cout << "\nSuccessfuly loaded brainfuck project (" << filepath << ")!\n\n"
                 "Executing project \"" << project.GetData().Name << "\n...\n\n";

    std::string filepathDirectory{ _Internal::ExportFileDirectory(filepath) };

    for (const auto& it : project.GetData().Sources)
    {
        if (!project.GetData().SharedMemory)
            Interpreter::ResetEnvironment();
        
        std::string correctFilepath{ filepathDirectory + it };
        
        std::cout << "[" << correctFilepath << "] => ";
        Interpreter::Interpret(correctFilepath, {
            Brainfucppk::InterpretationMode::File,
            Brainfucppk::GetImplementationFromString(project.GetData().Implementation),
        });
    }
}

void ProjectInterpreter::InterpretProject(const nlohmann::json& json)
{
}
