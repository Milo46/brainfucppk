#pragma once

#include <vector>
#include <string>

#include <nlohmann/json.hpp>

struct BrainfuckProjectData
{
    std::string Name;
    std::string Implementation;

    bool SharedMemory{ false };

    std::vector<std::string> Sources;
};

class BrainfuckProject
{
public:
    BrainfuckProject()  = default;
    ~BrainfuckProject() = default;

    const BrainfuckProjectData& GetData() const noexcept;

    bool ParseJson(const nlohmann::json& data);

private:
    BrainfuckProjectData m_Data;
};
