#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>

#include "BfImplementation.hpp"

struct JsonProjectInfo
{
    uint32_t ProjectVersion = 1u;

    std::string Name;
    std::string Implementation;
    
    bool IsSharingMemory = false;

    std::vector<std::string> Sources;
};

class BrainfuckInterpreter
{
public:
    class Error : public std::exception
    {
    public:
        Error(const char* message, std::size_t tokenIndex);
        std::size_t GetTokenIndex() const;

    private:
        std::size_t m_TokenIndex;
    };

public:
    BrainfuckInterpreter();
    ~BrainfuckInterpreter();

    //void InterpretSection(const std::string& source);
    void InterpretFile(const std::string& filepath);

    void ExecuteProject(const std::string& filepath);

private:
    void ResetEnvironment();

private:
    BrainfuckImplementation* m_Implementation = nullptr;

    unsigned char* m_Memory  = nullptr;
    unsigned char* m_Pointer = nullptr;
};
