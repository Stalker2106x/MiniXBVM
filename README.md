# Mini8BVM

## About

Mini8BVM is a Virtual machine emulating a SAP-1 Microcomputer in memory.
The VM is cross platform, and uses C++14.

## Contributors
+ Stabax ([http://stabax.org](http://stabax.org))
+ Maxime 'stalker2106' Martens

## License

This software is released under MIT License, which is defined inside "LICENSE" file.

## Getting Started

### Building program

These command lines should produce a binary in "./bin" folder.

    mkdir build
    cd build
    cmake ..
    make

### Usage

For now, the software does not provide any configuration, come back later!

### Instruction set

Here are the common keywords defined for this architecture

| keyword | binary | usage |
| --- | ---- | ---- |
| LDA | 0000 | Load addressed memory contents into accumulator |
| ADD | 0001 | Add addressed memory contents to accumulator |
| SUB | 0010 | Subtract addressed memory contents from accumulator |
| OUT | 1110 | Load accumulator data into output register |
| HLT | 1111 | Stop processing |