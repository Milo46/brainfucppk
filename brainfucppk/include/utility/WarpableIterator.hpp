#pragma once

#include <stdint.h>

template<typename _Ty>
class WarpableIterator
{
public:
    explicit WarpableIterator(_Ty* begin, _Ty* end);
    WarpableIterator(const WarpableIterator& other);

    void SetBegin(_Ty* newBegin);
    void SetEnd(_Ty* newEnd);

public:
    WarpableIterator& operator=(_Ty* poiner);

    WarpableIterator& operator+(const uint64_t units);
    WarpableIterator& operator-(const uint64_t units);

    WarpableIterator& operator+=(const uint64_t units);
    WarpableIterator& operator-=(const uint64_t units);

    WarpableIterator& operator++();
    WarpableIterator& operator--();

    /***/ _Ty& operator*() /***/;
    const _Ty& operator*() const;

private:
    _Ty* m_Pointer;
    _Ty* m_Begin;
    _Ty* m_End;
};

#include "WarpableIterator.inl"
