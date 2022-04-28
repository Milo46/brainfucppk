#include "core/BfInterpreter.hpp"
#include "core/BfErrors.hpp"

#include "utility/SemanticVersion.hpp"
#include "utility/FileData.hpp"

#include <string>

#include <nlohmann/json.hpp>

#define EXPECT_UNEXPECTED() \
    catch (...) { throw std::runtime_error{ "You stupid faggot!! [" __FILE__ ":" + std::to_string(__LINE__) + "]" }; }

/*
    #TODO: create three different interpreters: basic, file & project interpreters.
*/

struct JsonProjectData
{
    SemanticVersion ProjectVersion;

    std::string Name;
    std::string Implementation;

    bool SharedMemory{ false };

    std::vector<std::string> Sources;
};

class JsonProject
{
public:
    JsonProject()  = default;
    ~JsonProject() = default;

    JsonProjectData& GetData() noexcept
    {
        return m_Data;
    }

    bool ParseJson(const nlohmann::json& data)
    {
        try
        {
            m_Data.ProjectVersion = SemanticVersion{ static_cast<std::string>(data.at("projectVersion")) };
            m_Data.Name           = data.at("data").at("name");
            m_Data.Implementation = data.at("data").at("implementation");
            m_Data.SharedMemory   = data.at("data").at("sharedMemory");

            decltype(m_Data.Sources) tempSources{};
            tempSources.reserve(data.at("sources").size());

            for (const auto& it : data.at("sources"))
                tempSources.push_back(it);
            
            m_Data.Sources = std::move(tempSources);    
        }
        catch (nlohmann::json::exception& e)
        {
            return false;
        }

        return true;
    }

private:
    JsonProjectData m_Data;
};

namespace _Internal
{
    std::string ExportFileDirectory(const std::string& filepath)
    {
        return filepath.substr(0u, std::max(filepath.find_last_of('/')  + 1u,
                                            filepath.find_last_of('\\') + 1u));
    }
}

BrainfuckInterpreter::BrainfuckInterpreter(uint32_t memorySize)
    : m_MemorySize{ memorySize }, m_Output{}
{
    m_Memory  = new unsigned char[m_MemorySize];
    m_Pointer = m_Memory;

    for (size_t i = 0u; i < m_MemorySize; ++i)
        m_Memory[i] = 0;
}

BrainfuckInterpreter::~BrainfuckInterpreter()
{
    delete[] m_Memory;
}

void BrainfuckInterpreter::InterpretFile(const std::string& filepath)
{
    bool blankImplementation{ false };

    if (!m_Implementation)
    {
        m_Implementation = GetBrainfuckImplementation(BFImplementationEnum::Standard, m_Pointer);
        blankImplementation = true;
    }

    FileData fileData{ filepath, true };

    try
    {
        for (std::size_t i = 0u; i < fileData.GetSource().size(); ++i)
            m_Implementation->ResolveToken(fileData, i);
    }
    catch (EndProgram&) {}

    if (blankImplementation)
        delete m_Implementation;
}

void BrainfuckInterpreter::ExecuteProject(const std::string& filepath)
{
    JsonProject jsonProject{};
    nlohmann::json jsonData{};

    try
    {
        FileData jsonContent{ filepath, true };
        jsonData = nlohmann::json::parse(jsonContent.GetSource());
    }
    catch (nlohmann::json::parse_error&)
    {
        throw BrainfuckFileError::Create(filepath, "failed to parse json project file!");
    }
    EXPECT_UNEXPECTED()

    if (!jsonProject.ParseJson(jsonData))
        throw BrainfuckBasicError::Create("ill-formed json project!");

    std::cout << "\nSuccessfuly loaded brainfuck project (" << filepath << ")!\n\n"
                 "Executing project \"" << jsonProject.GetData().Name << "\"...\n";
    
    m_Implementation = GetBrainfuckImplementation(jsonProject.GetData().Implementation, m_Pointer);

    std::string filepathDirectory{ _Internal::ExportFileDirectory(filepath) };

    for (const auto& it : jsonProject.GetData().Sources)
    {
        if (!jsonProject.GetData().SharedMemory)
            BrainfuckInterpreter::ResetEnvironment();

        std::string correctFilepath{ filepathDirectory + it };

        std::cout << "[" << correctFilepath << "] -> ";
        InterpretFile(correctFilepath);
    }

    delete m_Implementation;
}

void BrainfuckInterpreter::ResetEnvironment()
{
    for (size_t i = 0u; i < m_MemorySize; ++i)
        m_Memory[i] = 0;
    m_Pointer = m_Memory;
}
