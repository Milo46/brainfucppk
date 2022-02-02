#include "BfInterpreter.hpp"

#include "BfConfiguration.hpp"
#include "BfTokens.hpp"

// todo: create header with macros

#define LOG(x) std::cout << #x << ": " << x << '\n'

#define THROW_BF_ERROR(_Message, _Index) \
    throw ::BrainfuckInterpreter::Error{ _Message, _Index }

static std::string ExportFileDirectory(const std::string& filepath)
{
    return filepath.substr(0u, std::max(filepath.find_last_of('/')  + 1u,
                                        filepath.find_last_of('\\') + 1u));
}

static std::string LoadFileContent(const std::string& filepath)
{
    auto file = std::ifstream{ filepath };

    if (!file.is_open())
        THROW_BF_ERROR("Failed to read the file!", 0u);

    auto fileContent = std::string{ std::istreambuf_iterator<char>(file), {} };
    file.close();

    return fileContent;
}

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
}

BrainfuckInterpreter::~BrainfuckInterpreter()
{
    delete[] m_Memory;
}

/*void BrainfuckInterpreter::InterpretSection(const std::string& source)
{
    for (std::size_t i = 0u; i < source.size(); ++i)
    {
        //m_Implementation->(source, i);

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
}*/

void BrainfuckInterpreter::InterpretFile(const std::string& filepath)
{
    if (!m_Implementation)
        m_Implementation = GetBrainfuckImplementation("Standard", m_Pointer);

    auto source = LoadFileContent(filepath);

    for (std::size_t i = 0u; i < source.size(); ++i)
        m_Implementation->ResolveToken(source, i);
}

void BrainfuckInterpreter::ExecuteProject(const std::string& filepath)
{
    JsonProjectInfo projectInfo{};

    try
    {
        // todo: pack loading json into project by it's method (maybe) (think before doing)

        auto fileContent = LoadFileContent(filepath);
        auto json        = nlohmann::json::parse(fileContent);

        projectInfo.ProjectVersion  = json.at("ProjectVersion");
        projectInfo.Name            = json.at("Name");
        projectInfo.Implementation  = json.at("Implementation");
        projectInfo.IsSharingMemory = json.at("ShareMemory");

        for (const auto& it : json.at("Sources"))
            projectInfo.Sources.push_back(it);

        std::cout << "Successfuly loaded brainfuck project (" << filepath << ")!\n\n";
    }
    catch (nlohmann::json::parse_error&)  { THROW_BF_ERROR("Failed to parse json project file!", 0u); }
    catch (nlohmann::json::out_of_range&) { THROW_BF_ERROR("Ill-formed json project file!", 0u); }
    catch (nlohmann::json::type_error&)   { THROW_BF_ERROR("Ill-formed json project file!", 0u); }

    std::cout << "Executing project \"" << projectInfo.Name << "\"...\n";
    
    m_Implementation = GetBrainfuckImplementation(projectInfo.Implementation, m_Pointer);

    auto filepathDirectory = ExportFileDirectory(filepath);

    for (const auto& it : projectInfo.Sources)
    {
        if (!projectInfo.IsSharingMemory)
            BrainfuckInterpreter::ResetEnvironment();

        auto correctFilepath = filepathDirectory + it;

        std::cout << "[" << correctFilepath << "] -> ";
        InterpretFile(correctFilepath);
    }

    delete m_Implementation;
}

void BrainfuckInterpreter::ResetEnvironment()
{
    for (size_t i = 0u; i < BrainfuckConfiguration::GetMemorySize(); ++i)
        m_Memory[i] = 0u;
    m_Pointer = m_Memory;
}
