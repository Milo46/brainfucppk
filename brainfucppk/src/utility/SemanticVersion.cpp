#include "utility/SemanticVersion.hpp"

SemanticVersion::SemanticVersion(const SemanticVersion& other)
    : Major{ other.Major }, Minor{ other.Minor }, Patch{ other.Patch } {}

SemanticVersion::SemanticVersion(const std::string& textRepresentation)
{
    std::stringstream sstream{ textRepresentation };

    (sstream >> Major).ignore();
    (sstream >> Minor).ignore();
    (sstream >> Patch).ignore();
}

SemanticVersion::SemanticVersion(uint32_t major, uint32_t minor, uint32_t patch)
    : Major{ major }, Minor{ minor }, Patch{ patch } {}

bool SemanticVersion::operator==(const SemanticVersion& other) const noexcept
{
    return (Major == other.Major && Minor == other.Minor && Patch == other.Patch);
}

bool SemanticVersion::operator!=(const SemanticVersion& other) const noexcept
{
    return !(*this == other);
}

namespace std
{
    std::string to_string(const SemanticVersion& version)
    {
        return std::to_string(version.Major) + '.' +
               std::to_string(version.Minor) + '.' +
               std::to_string(version.Patch);
    }
}
