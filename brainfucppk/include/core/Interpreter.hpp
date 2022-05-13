#pragma once

#include <optional>
#include <iostream>
#include <memory>
#include <string>

#include "core/Config.hpp"
#include "core/Implementation.hpp"

#include "utility/Noncopyable.hpp"
#include "utility/WarpableIterator.hpp"

#define SET_IMPLEMENTATION(_Implementation) \
    ImplementationSetter _implSetter{ this, _Implementation }

BRAINFUCPPK_BEGIN

enum class InterpretationMode
{
    Source = 0,
    File,

    Undefined = -1,
};

struct InterpretationConfig
{
    InterpretationMode Mode{ InterpretationMode::Source };
    ImplementationEnum Implementation{ ImplementationEnum::Standard };
};

class Interpreter : private NonCopyable<Interpreter>
{
    friend Implementation* Implementation::Create(Interpreter*, ImplementationEnum);
    friend Implementation* Implementation::Create(Interpreter*, const std::string&);

public:
    /* Special token which ends interpretation when thrown */
    struct EndProgram {};

private: /* Is it worth putting here inline and giving them value there? */
    static std::ostream& c_DefaultOutputStream; /* = std::cout */
    static std::istream& c_DefaultInputStream;  /* = std::cin  */

public:
    explicit Interpreter(const uint64_t memorySize);
    virtual ~Interpreter();

    void Interpret(
        const std::string& input,
        const InterpretationMode mode,
        const ImplementationEnum implementation = ImplementationEnum::Standard
    ) noexcept(false);

    void Interpret(const std::string& input, const InterpretationConfig& config) noexcept(false);

    void SetOutputStream(std::ostream& stream);
    void SetInputStream(std::istream& stream);

protected:
    /**
     * @brief RAII implementation setter for interpreter, fancy.
     */
    class ImplementationSetter
    {
    public:
        ImplementationSetter(Interpreter* owner, const ImplementationEnum implementation);
        ~ImplementationSetter();

    protected:
        Interpreter* const m_Owner;
    };

protected:
    void ResetEnvironment();

private:
    void InterpretSource(const std::string& source, const ImplementationEnum implementation);
    void InterpretFile(const std::string& filepath, const ImplementationEnum implementation);

public:
    Implementation* m_Implementation{ nullptr };

    uint64_t m_MemorySize;
    unsigned char* m_Memory;
    WarpableIterator<unsigned char> m_Pointer;

    std::ostream* m_OutputStream;
    std::istream* m_InputStream;
};

BRAINFUCPPK_END
