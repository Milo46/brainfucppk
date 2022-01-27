#include "BfInterpreter.hpp"

#include "BfConfiguration.hpp"
#include "BfTokens.hpp"

BrainfuckInterpreter::Error::Error(const char* message, size_t tokenIndex)
    : std::exception(message), m_TokenIndex(tokenIndex) {}

size_t BrainfuckInterpreter::Error::GetTokenIndex() const
{
    return m_TokenIndex;
}

BrainfuckInterpreter::BrainfuckInterpreter()
    : m_Memory(new unsigned char[BrainfuckConfiguration::GetMemorySize()]), m_Pointer(m_Memory),
    m_Implementation(GetBrainfuckImplementation(this))
{
    for (size_t i = 0u; i < BrainfuckConfiguration::GetMemorySize(); ++i)
        m_Memory[i] = 0u;
}

BrainfuckInterpreter::~BrainfuckInterpreter()
{
    delete[] m_Memory;
}

void BrainfuckInterpreter::InterpretSection(const std::string& tokens, size_t prevIndex)
{
    for (size_t i = 0u; i < tokens.size(); ++i)
    {
        switch (tokens[i])
        {
        case BrainfuckToken::IncrementPointer: m_Implementation->IncrementPointer(tokens, i);     break;
        case BrainfuckToken::DecrementPointer: m_Implementation->DecrementPointer(tokens, i);     break;
        case BrainfuckToken::IncrementValue:   m_Implementation->IncrementValue(tokens, i);       break;
        case BrainfuckToken::DecrementValue:   m_Implementation->DecrementValue(tokens, i);       break;
        case BrainfuckToken::Write:            m_Implementation->Write(tokens, i);                break;
        case BrainfuckToken::Read:             m_Implementation->Read(tokens, i);                 break;
        case BrainfuckToken::BeginLoop:        m_Implementation->BeginLoop(tokens, i, prevIndex); break;
        case BrainfuckToken::EndLoop:          m_Implementation->EndLoop(tokens, i, prevIndex);   break;
        }
    }
}

void BrainfuckInterpreter::InterpretFile(const std::string& filepath)
{
    std::fstream file(filepath, std::ios::in);

    if (!file.is_open())
        throw BrainfuckInterpreter::Error{ "Failed to read the file!", 0u };

    std::string fileContent(std::istreambuf_iterator<char>(file), {});
    file.close();

    return BrainfuckInterpreter::InterpretSection(fileContent, 0u);
}
