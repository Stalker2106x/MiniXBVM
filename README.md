![Logo](/MiniXBVM.png?raw=true)

[![Build Status](https://travis-ci.org/Stalker2106x/Mini8BVM.svg?branch=master)](https://travis-ci.org/Stalker2106x/Mini8BVM)

## About

Mini8BVM is a Graphical Virtual Machine emulating a SAP-X Microcomputer architecture written in C++.  
Binary includes a feature-rich IDE for SAP-X assembler and a compiler.  
Dynamic register/memory watches and step by step execution for better understanding of code flow.  

![VM Overview](/docs/overview.png?raw=true)

## Contributors
+ Stabax ([http://stabax.org](http://stabax.org))
+ Maxime 'stalker2106' Martens

## License

This software is released under MIT License, which is defined inside "LICENSE" file.

## Dependencies
+ FreeGLUT (OpenGL2)
+ Dear ImGUI
+ CMake

## Getting Started

### Building program

First, fetch git submodules:

    git submodule init --update

then, you need to build the SFML (UI) dependency:

    cd thirdparty/SFML
    mkdir build && cd build
    cmake .. -DBUILD_SHARED_LIBS=ON
    make

Move back to the root of the repository and start building the app.

    cd ../../
    mkdir build && cd build
    cmake ..
    make

### Hardware configuration

For optimisation purposes, the VM is compiled with static word size.
A few defines allow the user to recompile the software with different word size.
VM supports word sizes up to 18446744073709551615 bits (size_t underlying type)

### Instruction set

We use a custom implementation of SAP-1 which instructions are defined here

| keyword | binary | usage |
| --- | ---- | ---- |
| LDA | 0001 | Load addressed memory contents into accumulator |
| ADD | 0010 | Add addressed memory contents to accumulator |
| SUB | 0011 | Subtract addressed memory contents from accumulator |
| OUT | 1110 | Load accumulator data into output register |
| HLT | 1111 | Stop processing |
