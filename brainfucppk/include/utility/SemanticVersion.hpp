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

    SemanticVersion(const SemanticVersion& other);

    explicit SemanticVersion(const std::string& textRepresentation);

    SemanticVersion(uint32_t major, uint32_t minor, uint32_t patch);
    
    bool operator==(const SemanticVersion& other) const noexcept;
    bool operator!=(const SemanticVersion& other) const noexcept;
};

namespace std
{
    std::string to_string(const SemanticVersion& version);
}
