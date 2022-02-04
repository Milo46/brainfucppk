# 💫 Brainfucppk - Brainfuck Interpreter

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cca2ef348b2e449fb29015a63482827b)](https://www.codacy.com/gh/Milo46/brainfucppk/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Milo46/brainfucppk&amp;utm_campaign=Badge_Grade)

Simple and easy to use brainfuck interpreter with ability to merge
multiple source files into one thing and personalized options.

## 📖 How to start

To get started you have to create a project file which is
nothing other than a json file. Here's the example:

```json
{
    "ProjectVersion": 1,

    "Name": "Hello, World!",
    "Implementation": "Standard",

    "ShareMemory": false,

    "Sources": [
        "hello_world.bf",
        "fibonacci.bf"
    ]
}
```

Every json project file has to contain information about:
-   ProjectVersion: int -> what version of project file you're currently using (project version and interpreter version are not the same things),
-   Name: string -> project's name,
-   Implementation: string -> brainfuck's implementation which your source code is using and is being supported by interpreter,
-   ShareMemory: boolean -> determines whether memory is being reset between the execution of each source code in the project,
-   Sources: string[] -> list of all source files which will be interpreted.
