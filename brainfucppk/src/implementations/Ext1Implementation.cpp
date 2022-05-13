#include "implementations/Ext1Implementation.hpp"

#include "core/Interpreter.hpp"

BRAINFUCPPK_BEGIN

Ext1Implementation::Ext1Implementation(const WarpableIterator<unsigned char>& pointer, std::ostream& output, std::istream& input)
    : StandardImplementation(pointer, output, input) {}

bool Ext1Implementation::ResolveToken(const std::string& source, std::size_t& index)
{
    if (StandardImplementation::ResolveToken(source, index))
        return true;

    switch (source[index])
    {
    case static_cast<char>(Ext1Token::EndProgram):        EndProgram(source, index);        break;
    case static_cast<char>(Ext1Token::SetStorage):        SetStorage(source, index);        break;
    case static_cast<char>(Ext1Token::GetStorage):        GetStorage(source, index);        break;
    case static_cast<char>(Ext1Token::RightLogicalShift): RightLogicalShift(source, index); break;
    case static_cast<char>(Ext1Token::LeftLogicalShift):  LeftLogicalShift(source, index);  break;
    case static_cast<char>(Ext1Token::BitwiseNot):        BitwiseNot(source, index);        break;
    case static_cast<char>(Ext1Token::BitwiseXor):        BitwiseXor(source, index);        break;
    case static_cast<char>(Ext1Token::BitwiseAnd):        BitwiseAnd(source, index);        break;
    case static_cast<char>(Ext1Token::BitwiseOr):         BitwiseOr(source, index);         break;

    default: return false;
    }

    return true;
}

void Ext1Implementation::EndProgram(const std::string& sourceData, std::size_t& index)
{
    throw Interpreter::EndProgram{};
}

void Ext1Implementation::SetStorage(const std::string& sourceData, std::size_t& index)
{
    m_Storage = (*p_Pointer);
}

void Ext1Implementation::GetStorage(const std::string& sourceData, std::size_t& index)
{
    (*p_Pointer) = m_Storage;
}

void Ext1Implementation::RightLogicalShift(const std::string& sourceData, std::size_t& index)
{
    (*p_Pointer) >>= 1;
}

void Ext1Implementation::LeftLogicalShift(const std::string& sourceData, std::size_t& index)
{
    (*p_Pointer) <<= 1;
}

void Ext1Implementation::BitwiseNot(const std::string& sourceData, std::size_t& index)
{
    *p_Pointer = ~(*p_Pointer);
}

void Ext1Implementation::BitwiseXor(const std::string& sourceData, std::size_t& index)
{
    (*p_Pointer) ^= m_Storage;
}

void Ext1Implementation::BitwiseAnd(const std::string& sourceData, std::size_t& index)
{
    (*p_Pointer) &= m_Storage;
}

void Ext1Implementation::BitwiseOr(const std::string& sourceData, std::size_t& index)
{
    (*p_Pointer) |= m_Storage;
}

BRAINFUCPPK_END
