#include "UCException.hpp"

UCException::UCException(const char* message)
    : m_Message(message) {}

const char* UCException::What() const
{
    return m_Message;
}
