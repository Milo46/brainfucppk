#include "BrainfuckProject.hpp"

const BrainfuckProjectData& BrainfuckProject::GetData() const noexcept
{
    return m_Data;
}

bool BrainfuckProject::ParseJson(const nlohmann::json& data)
{
    try
    {
        m_Data.Name           = data.at("data").at("name");
        m_Data.Implementation = data.at("data").at("implementation");
        m_Data.SharedMemory   = data.at("data").at("sharedMemory");

        decltype(m_Data.Sources) tempSources{};
        tempSources.reserve(data.at("sources").size());

        for (const auto& it : data.at("sources"))
            tempSources.push_back(it);
        
        m_Data.Sources = std::move(tempSources);
    }
    catch (nlohmann::json::exception& e)
    {
        /* Clean data, so no rubbish stays. */
        m_Data = {};
        return false;
    }

    return true;
}
