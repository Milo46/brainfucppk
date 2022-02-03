#pragma once

enum class BrainfuckToken : char
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
