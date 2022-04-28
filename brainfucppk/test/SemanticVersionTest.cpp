#include <gtest/gtest.h>
#include <string>

#include "../include/utility/SemanticVersion.hpp"

TEST(BrainfuccpkTests, SemanticVersionConstructorTest)
{
    decltype(SemanticVersion::Major) majorExpected{ 2u };
    decltype(SemanticVersion::Minor) minorExpected{ 1u };
    decltype(SemanticVersion::Patch) patchExpected{ 7u };

    SemanticVersion version{
        majorExpected,
        minorExpected,
        patchExpected,
    };

    EXPECT_EQ(version.Major, majorExpected);
    EXPECT_EQ(version.Minor, minorExpected);
    EXPECT_EQ(version.Patch, patchExpected);
}

TEST(BrainfuccpkTests, SemanticVersionStringConstructorTest)
{
    decltype(SemanticVersion::Major) majorExpected{  21u };
    decltype(SemanticVersion::Minor) minorExpected{   1u };
    decltype(SemanticVersion::Patch) patchExpected{ 738u };

    std::string stringRepresentation{
        std::to_string(majorExpected) + '.' +
        std::to_string(minorExpected) + '.' +
        std::to_string(patchExpected)
    };

    SemanticVersion version{ stringRepresentation };

    EXPECT_EQ(version.Major, majorExpected);
    EXPECT_EQ(version.Minor, minorExpected);
    EXPECT_EQ(version.Patch, patchExpected);
}

TEST(BrainfuccpkTests, SemanticVersionEqOperatorTest)
{
    SemanticVersion version{ "2.1.7" };
    SemanticVersion versionCopy{ version };

    EXPECT_EQ(version, versionCopy);

    ++versionCopy.Major;

    EXPECT_NE(version, versionCopy);
}

TEST(BrainfuccpkTests, SemanticVersionToStringTest)
{
    std::string stringRepresentation{ "23.1.102" };

    SemanticVersion version{ stringRepresentation };

    EXPECT_EQ(stringRepresentation, std::to_string(version));
}

/* JEDZENIE ZARAZ BEDE JADL! */
