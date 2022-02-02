#include "ExtendedBfImplementation.hpp"

#include "core/BfInterpreter.hpp"

ExtendedBrainfuckImplementation::ExtendedBrainfuckImplementation(unsigned char* pointer)
    : StandardBrainfuckImplementation(pointer) {}

bool ExtendedBrainfuckImplementation::ResolveToken(const std::string& source, std::size_t& index)
{
    if (StandardBrainfuckImplementation::ResolveToken(source, index))
        return true;

    switch (source[index])
    {
    case static_cast<char>(ExtendedBrainfuckToken::EndProgram):        EndProgram(source, index); break;
    case static_cast<char>(ExtendedBrainfuckToken::SetStorage):        SetStorage(source, index); break;
    case static_cast<char>(ExtendedBrainfuckToken::GetStorage):        GetStorage(source, index); break;
    case static_cast<char>(ExtendedBrainfuckToken::RightLogicalShift): RightLogicalShift(source, index); break;
    case static_cast<char>(ExtendedBrainfuckToken::LeftLogicalShift):  LeftLogicalShift(source, index); break;
    case static_cast<char>(ExtendedBrainfuckToken::BitwiseNot):        BitwiseNot(source, index); break;
    case static_cast<char>(ExtendedBrainfuckToken::BitwiseXor):        BitwiseXor(source, index); break;
    case static_cast<char>(ExtendedBrainfuckToken::BitwiseAnd):        BitwiseAnd(source, index); break;
    case static_cast<char>(ExtendedBrainfuckToken::BitwiseOr):         BitwiseOr(source, index); break;

    default: return false;
    }

    return true;
}

void ExtendedBrainfuckImplementation::EndProgram(const std::string& source, std::size_t& index)
{
    throw BrainfuckInterpreter::EndProgram{};
}

void ExtendedBrainfuckImplementation::SetStorage(const std::string& source, std::size_t& index)
{
    m_Storage = (*p_Pointer);
}

void ExtendedBrainfuckImplementation::GetStorage(const std::string& source, std::size_t& index)
{
    (*p_Pointer) = m_Storage;
}

void ExtendedBrainfuckImplementation::RightLogicalShift(const std::string& source, std::size_t& index)
{
    (*p_Pointer) >>= 1;
}

void ExtendedBrainfuckImplementation::LeftLogicalShift(const std::string& source, std::size_t& index)
{
    (*p_Pointer) <<= 1;
}

void ExtendedBrainfuckImplementation::BitwiseNot(const std::string& source, std::size_t& index)
{
    *p_Pointer = ~(*p_Pointer);
}

void ExtendedBrainfuckImplementation::BitwiseXor(const std::string& source, std::size_t& index)
{
    (*p_Pointer) ^= m_Storage;
}

void ExtendedBrainfuckImplementation::BitwiseAnd(const std::string& source, std::size_t& index)
{
    (*p_Pointer) &= m_Storage;
}

void ExtendedBrainfuckImplementation::BitwiseOr(const std::string& source, std::size_t& index)
{
    (*p_Pointer) |= m_Storage;
}
