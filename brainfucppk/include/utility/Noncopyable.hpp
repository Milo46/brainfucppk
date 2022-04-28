#pragma once

template<typename _Ty>
struct NonCopyable
{
public:
    NonCopyable(const NonCopyable&) = delete;
    _Ty& operator=(const _Ty&)      = delete;

protected:
    NonCopyable()  = default;
    ~NonCopyable() = default;
};
