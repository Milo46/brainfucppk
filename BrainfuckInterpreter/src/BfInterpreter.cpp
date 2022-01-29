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
{
    m_Memory  = new unsigned char[BrainfuckConfiguration::GetMemorySize()];
    m_Pointer = m_Memory;

    for (size_t i = 0u; i < BrainfuckConfiguration::GetMemorySize(); ++i)
        m_Memory[i] = 0u;

    m_Implementation = GetBrainfuckImplementation(m_Pointer);
}

BrainfuckInterpreter::~BrainfuckInterpreter()
{
    delete[] m_Memory;
    delete m_Implementation;
}

void BrainfuckInterpreter::InterpretSection(const std::string& source, size_t prevIndex)
{
    for (std::size_t i = 0u; i < source.size(); ++i)
    {
        switch (source[i])
        {
        case BrainfuckToken::IncrementPointer: m_Implementation->IncrementPointer(source, i); break;
        case BrainfuckToken::DecrementPointer: m_Implementation->DecrementPointer(source, i); break;
        case BrainfuckToken::IncrementValue:   m_Implementation->IncrementValue(source, i);   break;
        case BrainfuckToken::DecrementValue:   m_Implementation->DecrementValue(source, i);   break;
        case BrainfuckToken::Write:            m_Implementation->Write(source, i);            break;
        case BrainfuckToken::Read:             m_Implementation->Read(source, i);             break;
        case BrainfuckToken::BeginLoop:        m_Implementation->BeginLoop(source, i);        break;
        case BrainfuckToken::EndLoop:          m_Implementation->EndLoop(source, i);          break;

        default: break; // ignore every other character / undefined token
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
