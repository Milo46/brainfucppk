# 💫 Brainfucppk - Brainfuck Interpreter

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/cca2ef348b2e449fb29015a63482827b)](https://www.codacy.com/gh/Milo46/brainfucppk/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Milo46/brainfucppk&amp;utm_campaign=Badge_Grade)

Simple and easy to use brainfuck interpreter with ability to merge
multiple source files into one thing and personalized options.

## 💪 TODO

* Add command line arguments processing to the application.
* Change the way of handling different implementations.
* Create reliable tests for library and application as well.
* Improve README.md.

## 📖 How to start

To get started you have to create a project file which is
nothing other than a json file. Here's the example:

```json
// project.json
{
    "data": {
        "name": "Hello, World!",
        "implementation": "Extended1",
        "sharedMemory": false
    },
    "sources": [
        "hello_world.bf",
        "hello_world_ext1.bf"
    ]
}
```
