#include "utility/FileData.hpp"
#include "core/BfErrors.hpp"

#include <fstream>

FileData::FileData(const std::string& filepath, bool loadSource)
    : m_Filepath{ filepath }, m_Source{}
{
    if (!loadSource) return;

    if (!FileData::LoadSource())
        throw BrainfuckFileError::Create(filepath, "failed to load the content of the file.");
}

const std::string& FileData::GetFilepath() const noexcept
{
    return m_Filepath;
}

const std::string& FileData::GetSource() const noexcept
{
    return m_Source;
}

bool FileData::LoadSource() noexcept
{
    std::ifstream file{ m_Filepath };

    if (!file.is_open())
        return false;

    m_Source = std::string{ std::istreambuf_iterator<char>(file), {} };
    file.close();

    return true;
}
