#include "implementations/Ext1BfImplementation.hpp"

#include "core/BfInterpreter.hpp"

Ext1BrainfuckImplementation::Ext1BrainfuckImplementation(unsigned char* pointer)
    : StandardBrainfuckImplementation(pointer) {}

bool Ext1BrainfuckImplementation::ResolveToken(const FileData& sourceData, std::size_t& index)
{
    if (StandardBrainfuckImplementation::ResolveToken(sourceData, index))
        return true;

    switch (sourceData.GetSource()[index])
    {
    case static_cast<char>(Ext1BrainfuckToken::EndProgram):        EndProgram(sourceData, index);        break;
    case static_cast<char>(Ext1BrainfuckToken::SetStorage):        SetStorage(sourceData, index);        break;
    case static_cast<char>(Ext1BrainfuckToken::GetStorage):        GetStorage(sourceData, index);        break;
    case static_cast<char>(Ext1BrainfuckToken::RightLogicalShift): RightLogicalShift(sourceData, index); break;
    case static_cast<char>(Ext1BrainfuckToken::LeftLogicalShift):  LeftLogicalShift(sourceData, index);  break;
    case static_cast<char>(Ext1BrainfuckToken::BitwiseNot):        BitwiseNot(sourceData, index);        break;
    case static_cast<char>(Ext1BrainfuckToken::BitwiseXor):        BitwiseXor(sourceData, index);        break;
    case static_cast<char>(Ext1BrainfuckToken::BitwiseAnd):        BitwiseAnd(sourceData, index);        break;
    case static_cast<char>(Ext1BrainfuckToken::BitwiseOr):         BitwiseOr(sourceData, index);         break;

    default: return false;
    }

    return true;
}

void Ext1BrainfuckImplementation::EndProgram(const FileData& sourceData, std::size_t& index)
{
    throw BrainfuckInterpreter::EndProgram{};
}

void Ext1BrainfuckImplementation::SetStorage(const FileData& sourceData, std::size_t& index)
{
    m_Storage = (*p_Pointer);
}

void Ext1BrainfuckImplementation::GetStorage(const FileData& sourceData, std::size_t& index)
{
    (*p_Pointer) = m_Storage;
}

void Ext1BrainfuckImplementation::RightLogicalShift(const FileData& sourceData, std::size_t& index)
{
    (*p_Pointer) >>= 1;
}

void Ext1BrainfuckImplementation::LeftLogicalShift(const FileData& sourceData, std::size_t& index)
{
    (*p_Pointer) <<= 1;
}

void Ext1BrainfuckImplementation::BitwiseNot(const FileData& sourceData, std::size_t& index)
{
    *p_Pointer = ~(*p_Pointer);
}

void Ext1BrainfuckImplementation::BitwiseXor(const FileData& sourceData, std::size_t& index)
{
    (*p_Pointer) ^= m_Storage;
}

void Ext1BrainfuckImplementation::BitwiseAnd(const FileData& sourceData, std::size_t& index)
{
    (*p_Pointer) &= m_Storage;
}

void Ext1BrainfuckImplementation::BitwiseOr(const FileData& sourceData, std::size_t& index)
{
    (*p_Pointer) |= m_Storage;
}
