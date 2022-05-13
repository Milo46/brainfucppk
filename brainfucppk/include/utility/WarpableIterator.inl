#include "WarpableIterator.hpp"

template<typename _Ty>
WarpableIterator<_Ty>::WarpableIterator(_Ty* begin, _Ty* end)
    : m_Pointer{ begin }, m_Begin{ begin }, m_End{ end } {}

template<typename _Ty>
WarpableIterator<_Ty>::WarpableIterator(const WarpableIterator& other)
    : m_Pointer{ other.m_Pointer }, m_Begin{ other.m_Begin }, m_End{ other.m_End } {}

template<typename _Ty>
void WarpableIterator<_Ty>::SetBegin(_Ty* newBegin)
{
    m_Begin = newBegin;
}

template<typename _Ty>
void WarpableIterator<_Ty>::SetEnd(_Ty* newEnd)
{
    m_End = newEnd;
}

template<typename _Ty>
WarpableIterator<_Ty>& WarpableIterator<_Ty>::operator=(_Ty* pointer)
{
    m_Pointer = pointer;
    return *this;
}

template<typename _Ty>
WarpableIterator<_Ty>& WarpableIterator<_Ty>::operator+(const uint64_t units)
{
    if (m_Pointer + units < m_End)
    {
        m_Pointer += units;
        return *this;
    }

    std::ptrdiff_t delta{ (m_Pointer + units) - m_End };
    std::ptrdiff_t size{ m_End - m_Begin };

    m_Pointer = m_Begin + (delta % size);
    return *this;
}

template<typename _Ty>
WarpableIterator<_Ty>& WarpableIterator<_Ty>::operator-(const uint64_t units)
{
    if (m_Pointer - units >= m_Begin)
    {
        m_Pointer -= units;
        return *this;
    }

    std::ptrdiff_t delta{ m_Begin - (m_Pointer - units) };
    std::ptrdiff_t size{ m_End - m_Begin };

    m_Pointer = m_End - (delta % size);
    return *this;
}

template<typename _Ty>
WarpableIterator<_Ty>& WarpableIterator<_Ty>::operator+=(const uint64_t units)
{
    return (*this + units);
}

template<typename _Ty>
WarpableIterator<_Ty>& WarpableIterator<_Ty>::operator-=(const uint64_t units)
{
    return (*this - units);
}

template<typename _Ty>
WarpableIterator<_Ty>& WarpableIterator<_Ty>::operator++()
{
    return (*this + 1);
}

template<typename _Ty>
WarpableIterator<_Ty>& WarpableIterator<_Ty>::operator--()
{
    return (*this - 1);
}

template<typename _Ty>
_Ty& WarpableIterator<_Ty>::operator*()
{
    return *m_Pointer;
}

template<typename _Ty>
const _Ty& WarpableIterator<_Ty>::operator*() const
{
    return *m_Pointer;
}
