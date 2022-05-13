#pragma once

#include "core/Implementation.hpp"

#include <map>

BRAINFUCPPK_BEGIN

enum class StandardToken : char
{
    IncrementPointer = '>',
    DecrementPointer = '<',
    IncrementValue   = '+',
    DecrementValue   = '-',
    Write            = '.',
    Read             = ',',
    BeginLoop        = '[',
    EndLoop          = ']',

    End,
};

class StandardImplementation : public Implementation
{
public:
    StandardImplementation(const WarpableIterator<unsigned char>& pointer, std::ostream& output, std::istream& input);

protected:
    virtual bool ResolveToken(const std::string& source, std::size_t& index) noexcept(false) override;

private:
    void IncrementPointer(const std::string& source, std::size_t& index);
    void DecrementPointer(const std::string& source, std::size_t& index);
    void IncrementValue(const std::string& source, std::size_t& index);
    void DecrementValue(const std::string& source, std::size_t& index);
    void Write(const std::string& source, std::size_t& index);
    void Read(const std::string& source, std::size_t& index);
    void BeginLoop(const std::string& source, std::size_t& index);
    void EndLoop(const std::string& source, std::size_t& index);

private:
    /* The code isn't ready for that kind of thing yet. */
    // bool IsThisLoopInfinite(const std::string& source, const std::size_t bracketPosition) const;

private:
    std::map<std::size_t, std::size_t> m_LoopsPositions;
};

BRAINFUCPPK_END
