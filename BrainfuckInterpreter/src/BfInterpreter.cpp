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

void BrainfuckInterpreter::InterpretSection(const std::string& source)
{
    for (std::size_t i = 0u; i < source.size(); ++i)
    {
        //m_Implementation->GetMethod(source[i])(source, i);

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
    auto file = std::ifstream{ filepath };

    if (!file.is_open())
        throw BrainfuckInterpreter::Error{ "Failed to read the file!", 0u };

    auto fileContent = std::string{ std::istreambuf_iterator<char>(file), {} };
    file.close();

    return BrainfuckInterpreter::InterpretSection(fileContent);
}

void BrainfuckInterpreter::LoadProject(const std::string& filepath)
{
    auto file = std::ifstream{ filepath };

    if (!file.is_open())
        throw BrainfuckInterpreter::Error{ "Failed to load the project file!", 0u };

    auto json = nlohmann::json::parse(file);

    if (!ValidateProjectFile(json))
        throw BrainfuckInterpreter::Error{ "Ill constructed project file!", 0u };
}

bool BrainfuckInterpreter::ValidateProjectFile(const nlohmann::json& json)
{
    //if (!json.contains("Name") || !json["Name"].is_string()) return false;

    try
    {
        const std::string& name           = json.at("Name");
        const std::string& implementation = json.at("Implementation");
        const bool& shareMemory           = json.at("ShareMemory");
        const nlohmann::json& sources     = json.at("Sources");
    }
    catch (nlohmann::json::out_of_range& e) { return false; }
    catch (nlohmann::json::type_error& e) { return false; }
    catch (...) { return false; }

    return true;
}
