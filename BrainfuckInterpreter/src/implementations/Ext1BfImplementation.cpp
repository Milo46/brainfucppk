#include "Ext1BfImplementation.hpp"

#include "core/BfInterpreter.hpp"

Ext1BrainfuckImplementation::Ext1BrainfuckImplementation(unsigned char* pointer)
    : StandardBrainfuckImplementation(pointer) {}

bool Ext1BrainfuckImplementation::ResolveToken(const std::string& source, std::size_t& index)
{
    if (StandardBrainfuckImplementation::ResolveToken(source, index))
        return true;

    switch (source[index])
    {
    case static_cast<char>(Ext1BrainfuckToken::EndProgram):        EndProgram(source, index); break;
    case static_cast<char>(Ext1BrainfuckToken::SetStorage):        SetStorage(source, index); break;
    case static_cast<char>(Ext1BrainfuckToken::GetStorage):        GetStorage(source, index); break;
    case static_cast<char>(Ext1BrainfuckToken::RightLogicalShift): RightLogicalShift(source, index); break;
    case static_cast<char>(Ext1BrainfuckToken::LeftLogicalShift):  LeftLogicalShift(source, index); break;
    case static_cast<char>(Ext1BrainfuckToken::BitwiseNot):        BitwiseNot(source, index); break;
    case static_cast<char>(Ext1BrainfuckToken::BitwiseXor):        BitwiseXor(source, index); break;
    case static_cast<char>(Ext1BrainfuckToken::BitwiseAnd):        BitwiseAnd(source, index); break;
    case static_cast<char>(Ext1BrainfuckToken::BitwiseOr):         BitwiseOr(source, index); break;

    default: return false;
    }

    return true;
}

void Ext1BrainfuckImplementation::EndProgram(const std::string& source, std::size_t& index)
{
    throw BrainfuckInterpreter::EndProgram{};
}

void Ext1BrainfuckImplementation::SetStorage(const std::string& source, std::size_t& index)
{
    m_Storage = (*p_Pointer);
}

void Ext1BrainfuckImplementation::GetStorage(const std::string& source, std::size_t& index)
{
    (*p_Pointer) = m_Storage;
}

void Ext1BrainfuckImplementation::RightLogicalShift(const std::string& source, std::size_t& index)
{
    (*p_Pointer) >>= 1;
}

void Ext1BrainfuckImplementation::LeftLogicalShift(const std::string& source, std::size_t& index)
{
    (*p_Pointer) <<= 1;
}

void Ext1BrainfuckImplementation::BitwiseNot(const std::string& source, std::size_t& index)
{
    // Not sure if works with `unsigned char` or should change to `char` for memory and pointer
    *p_Pointer = ~(*p_Pointer);
}

void Ext1BrainfuckImplementation::BitwiseXor(const std::string& source, std::size_t& index)
{
    (*p_Pointer) ^= m_Storage;
}

void Ext1BrainfuckImplementation::BitwiseAnd(const std::string& source, std::size_t& index)
{
    (*p_Pointer) &= m_Storage;
}

void Ext1BrainfuckImplementation::BitwiseOr(const std::string& source, std::size_t& index)
{
    (*p_Pointer) |= m_Storage;
}
