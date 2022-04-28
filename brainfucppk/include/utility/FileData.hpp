#pragma once

#include <string>
#include <stdexcept>

class FileData
{
public:
    explicit FileData(const std::string& filepath, bool loadSource = true) noexcept(false);

    const std::string& GetFilepath() const noexcept;
    const std::string& GetSource() const noexcept;

    bool LoadSource() noexcept;

private:
    std::string m_Filepath;
    std::string m_Source;
};
