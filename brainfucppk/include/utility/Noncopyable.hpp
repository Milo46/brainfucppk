#pragma once

template<typename _Ty>
class NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    _Ty& operator=(const _Ty&)      = delete;

protected:
    NonCopyable()  = default;
    ~NonCopyable() = default;
};
