#ifndef BRAINFUCK_ATTRIBUTES_HPP_INCLUDED
#define BRAINFUCK_ATTRIBUTES_HPP_INCLUDED

#define BRAINFUCK_NODISCARD(_Message) [[nodiscard(_Message)]]

#define BRAINFUCK_NODISCARD_RESULT() \
    BRAINFUCK_NODISCARD("Returns brainfuck interpretation result!")

#endif
