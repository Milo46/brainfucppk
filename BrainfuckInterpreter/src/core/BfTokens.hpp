#pragma once

enum BrainfuckToken : char
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
