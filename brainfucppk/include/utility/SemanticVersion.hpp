#pragma once

#include <string>
#include <sstream>

struct SemanticVersion
{
    uint32_t Major{ 0u };
    uint32_t Minor{ 0u };
    uint32_t Patch{ 0u };

    SemanticVersion()  = default;
    ~SemanticVersion() = default;

    SemanticVersion(const SemanticVersion& other)
        : Major{ other.Major }, Minor{ other.Minor }, Patch{ other.Patch } {}

    explicit SemanticVersion(const std::string& textRepresentation)
    {
        std::stringstream sstream{ textRepresentation };

        uint32_t number{};
        sstream >> number; Major = number; sstream.ignore();
        sstream >> number; Minor = number; sstream.ignore();
        sstream >> number; Patch = number; sstream.ignore();
    }

    SemanticVersion(uint32_t major, uint32_t minor, uint32_t patch)
        : Major{ major }, Minor{ minor }, Patch{ patch } {}
    
    bool operator==(const SemanticVersion& other) const noexcept
    {
        return (Major == other.Major && Minor == other.Minor && Patch == other.Patch);
    }

    bool operator!=(const SemanticVersion& other) const noexcept
    {
        return !(*this == other);
    }
};

namespace std
{
    std::string to_string(const SemanticVersion& version)
    {
        return std::to_string(version.Major) + '.' +
               std::to_string(version.Minor) + '.' +
               std::to_string(version.Patch);
    }
}
