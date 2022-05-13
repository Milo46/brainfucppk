#include "core/Interpreter.hpp"
#include "core/Errors.hpp"

#include "utility/SemanticVersion.hpp"

#include <fstream>
#include <string>

BRAINFUCPPK_BEGIN

namespace _Internal
{
    bool LoadFileContent(std::string& target, const std::string& filepath)
    {
        std::ifstream file{ filepath };

        if (!file.is_open())
            return false;
        
        target = std::string{ std::istreambuf_iterator<char>(file), {} };
        file.close();

        return true;
    }

    bool LoadFileContent(std::string& target, std::ifstream& file)
    {
        if (!file.is_open())
            return false;

        file.clear();
        file.seekg(0, std::ios::beg);

        target = std::string{ std::istreambuf_iterator<char>(file), {} };
        
        return true;
    }
}

std::ostream& Interpreter::c_DefaultOutputStream = std::cout;
std::istream& Interpreter::c_DefaultInputStream  = std::cin;

Interpreter::Interpreter(const uint64_t memorySize)
    : m_MemorySize{ memorySize }, m_Memory{ new unsigned char[m_MemorySize] },
    m_Pointer{ m_Memory, m_Memory + m_MemorySize },
    m_OutputStream{ &c_DefaultOutputStream }, m_InputStream{ &c_DefaultInputStream }
{
    Interpreter::ResetEnvironment();
}

Interpreter::~Interpreter()
{
    delete[] m_Memory;
}

void Interpreter::Interpret(const std::string& input, const InterpretationMode mode, const ImplementationEnum implementation)
{
    switch (mode)
    {
    case InterpretationMode::Source: Interpreter::InterpretSource(input, implementation); break;
    case InterpretationMode::File:   Interpreter::InterpretFile(input, implementation);   break;

    default:
        /* throw an error about invalid interpretation mode! */
        throw InterpreterError::Create({}, {}, "invalid interpretation mode!");
    }
}

void Interpreter::Interpret(const std::string& input, const InterpretationConfig& config)
{
    Interpreter::Interpret(input, config.Mode, config.Implementation);
}

void Interpreter::SetOutputStream(std::ostream& stream)
{
    m_OutputStream = &stream;
}

void Interpreter::SetInputStream(std::istream& stream)
{
    m_InputStream = &stream;
}

Interpreter::ImplementationSetter::ImplementationSetter(Interpreter* owner, const ImplementationEnum implementation)
    : m_Owner{ owner }
{
    m_Owner->m_Implementation = Implementation::Create(m_Owner, implementation);
}

Interpreter::ImplementationSetter::~ImplementationSetter()
{
    delete m_Owner->m_Implementation;
}

void Interpreter::InterpretSource(const std::string& source, const ImplementationEnum implementation)
{
    SET_IMPLEMENTATION(implementation);

    std::size_t index{};

    try
    {
        for (; index < source.size(); ++index)
            m_Implementation->ResolveToken(source, index);
    }
    catch (BasicError& e)
    {
        throw InterpreterError::Create("only-source", index, e.what());
    }
    catch (EndProgram&) {}
}

void Interpreter::InterpretFile(const std::string& filepath, const ImplementationEnum implementation)
{
    SET_IMPLEMENTATION(implementation);

    std::string source{};
    std::size_t index{};

    if (!_Internal::LoadFileContent(source, filepath))
        throw InterpreterError::Create(filepath, index, "couldn't load the file's content!");
    
    try
    {
        for (; index < source.size(); ++index)
            m_Implementation->ResolveToken(source, index);
    }
    catch (BasicError& e)
    {
        throw InterpreterError::Create(filepath, index, e.what());
    }
    catch (EndProgram&) {}
}

void Interpreter::ResetEnvironment()
{
    m_Pointer = m_Memory;

    for (std::size_t i = 0u; i < m_MemorySize; ++i)
        m_Memory[i] = 0u;
}

BRAINFUCPPK_END
