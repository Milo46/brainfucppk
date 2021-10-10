#include "BrainfuckInterpreter.hpp"

BrainfuckIntrepreter::Error::Error(const char* message, size_t tokenIndex)
    : UCException(message), m_TokenIndex(tokenIndex) {}

size_t BrainfuckIntrepreter::Error::GetTokenIndex() const
{
    return m_TokenIndex;
}

BrainfuckIntrepreter::BrainfuckIntrepreter(size_t memorySize)
{
    m_Memory  = new unsigned char[memorySize];
    m_Pointer = m_Memory;

    for (size_t i = 0u; i < memorySize; ++i)
        m_Memory[i] = 0u;
}

BrainfuckIntrepreter::~BrainfuckIntrepreter()
{
    delete[] m_Memory;
}

std::string BrainfuckIntrepreter::InterpretSection(const std::string& tokens, size_t start)
{
    std::string output = "";
    for (size_t i = 0u; i < tokens.size(); ++i)
    {
        switch (tokens[i])
        {
        case '>': ++m_Pointer; break;
        case '<': --m_Pointer; break;

        case '+': ++(*m_Pointer); break;
        case '-': --(*m_Pointer); break;

        case '.': output += (*m_Pointer); break;
        case ',': { char in = 0; std::cin >> in; *m_Pointer = in; break; }

        case '[':
        {
            size_t subSectionEndIndex = i;
            size_t bracketLevel = 1u;
            while (bracketLevel > 0 && ++subSectionEndIndex)
            {
                if (subSectionEndIndex == tokens.size())
                    throw ::BrainfuckIntrepreter::Error{ "Failed to find ending bracket!", start + i };

                switch (tokens[subSectionEndIndex])
                {
                case '[': ++bracketLevel; break;
                case ']': --bracketLevel; break;
                }
            }

            // Automatically omits blank loops
            if (subSectionEndIndex - 1 != i) while (*m_Pointer != 0)
                output += InterpretSection(tokens.substr(i + 1, subSectionEndIndex - i - 1), start + i);

            i = subSectionEndIndex;
            break;
        }

        case ']':
            throw ::BrainfuckIntrepreter::Error{ "Found ending bracket alone!", start + i };
            break;
        }
    }

    return output;
}

std::string BrainfuckIntrepreter::InterpretFile(const std::string& filepath)
{
    std::fstream file(filepath, std::ios::in);

    if (!file.is_open())
        throw BrainfuckIntrepreter::Error{ "Failed to read the file!", 0u };

    std::string fileContent(std::istreambuf_iterator<char>(file), {});
    file.close();

    return BrainfuckIntrepreter::InterpretSection(fileContent, 0u);
}
