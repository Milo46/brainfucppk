#pragma once

#include <nlohmann/json.hpp>

#include "core/Interpreter.hpp"

class ProjectInterpreter : public Brainfucppk::Interpreter
{
public:
    ProjectInterpreter(const uint64_t memorySize);
    virtual ~ProjectInterpreter();

    void InterpretProject(const std::string& filepath);
    void InterpretProject(const nlohmann::json& json);
};
