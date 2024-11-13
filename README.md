# LC4 Disassembler Project

This project implements a disassembler for the LC4 instruction set. It reads LC4 object files, parses the instructions and data, and outputs a human-readable assembly listing.

## Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Compilation and Execution](#compilation-and-execution)
- [Usage](#usage)
- [File Descriptions](#file-descriptions)
- [Sample Output](#sample-output)
- [LC4 Instruction Set](#lc4-instruction-set)
- [Notes](#notes)

## Overview

The program mimics the PennSim loader and disassembler. It performs the following steps:

1. Loads LC4 object files containing code, data, and symbols.
2. Parses the object files and constructs a memory linked list.
3. Disassembles the machine code into assembly instructions.
4. Outputs the contents of the memory, including addresses, contents, labels, and assembly instructions.

## Project Structure

```
./submit
├── lc4_disassembler.c
├── lc4_disassembler.h
├── lc4_loader.c
├── lc4_loader.h
├── lc4_memory.c
├── lc4_memory.h
├── lc4.c
└── Makefile
```

- `lc4.c`: The main driver of the program.
- `lc4_memory.*`: Implements the memory linked list and related helper functions.
- `lc4_loader.*`: Handles loading and parsing of the LC4 object files.
- `lc4_disassembler.*`: Contains the logic for disassembling machine code into assembly instructions.
- `Makefile`: Automates the compilation process.

## Compilation and Execution

### Prerequisites

- GCC compiler
- Make utility

### Compilation

Run the following command to compile the project:

```bash
cd ./submit
make all
```

This will produce an executable named `lc4`.

### Execution

To run the disassembler, use:

```bash
./lc4 <object_file.obj>
```

Replace `<object_file.obj>` with the path to your LC4 object file.

## Usage

1. **Compile the program** using the provided `Makefile`.
2. **Run the executable** with an LC4 object file as an argument.
3. **View the output**, which displays the labels, addresses, contents, and assembly instructions.

Example:

```bash
./lc4 example.obj
```

## File Descriptions

### `lc4.c`

- Initializes the memory linked list.
- Parses command-line arguments to get the object file name.
- Calls functions to load the object file, disassemble the instructions, print the memory contents, and clean up.

### `lc4_memory.h` and `lc4_memory.c`

- Defines the `row_of_memory` struct representing each memory location.
- Implements functions to:
  - Add nodes to the memory linked list.
  - Search for nodes by address or opcode.
  - Print the memory contents.
  - Delete the memory linked list.

### `lc4_loader.h` and `lc4_loader.c`

- Handles opening the object file.
- Parses the object file sections:
  - Code (`0xCADE`), Data (`0xDADA`), and Symbol (`0xC3B7`) sections.
- Populates the memory linked list with addresses, contents, and labels.

### `lc4_disassembler.h` and `lc4_disassembler.c`

- Contains the `reverse_assemble` function.
- Disassembles machine code instructions into their assembly equivalents.
- Supports various LC4 instructions as per the instruction set.

### `Makefile`

- Automates the compilation process.
- Usage:
  - `make all`: Compiles the project.
  - `make clean`: Cleans up object files.
  - `make clobber`: Cleans up object files and the executable.

## Sample Output

When running the program with a valid LC4 object file, the output will display the memory contents in the following format:

```
<label>              <address>            <contents>           <assembly>
MAIN                 0000                 9420                 
                     0001                 D540                 
                     0002                 16A5                 ADD R3, R2, #5
FOR_LOOP             0003                 2403                 
                     0004                 0603                 BRzp #3
                     0005                 4801                 
                     0006                 14A1                 ADD R2, R2, #1
                     0007                 CFFB                 
END_FOR_LOOP         0008                 C81B                 
SUB_FACTORIAL        0010                 6080                 
                     0011                 2100                 
                     0012                 0A02                 BRnp #2
                     0013                 9201                 
                     0014                 C80D                 
END_IF1              0015                 0202                 BRp #2
                     0016                 93FF                 
                     0017                 C80A                 
END_IF2              0018                 2107                 
                     0019                 0C02                 BRnz #2
                     001A                 93FF                 
                     001B                 C806                 
END_IF3              001C                 1220                 ADD R1, R0, #0
LOOP                 001D                 2101                 
                     001E                 0C03                 BRnz #3
                     001F                 103F                 ADD R0, R0, #-1
                     0020                 1248                 MUL R1, R1, R0
                     0021                 CFFB                 
END_SUB_FACTORIAL    0022                 7280                 
                     0023                 C1C0                 
END                  0024                 0000                 
VALUES               4020                 0006                 
                     4021                 0005                 
                     4022                 0008                 
                     4023                 000A                 
                     4024                 FFFB                 TRAP xFB
```

- **Label**: Any label associated with the memory address.
- **Address**: The memory address in hexadecimal.
- **Contents**: The machine code at that address.
- **Assembly**: The disassembled assembly instruction.

## LC4 Instruction Set

The disassembler supports the LC4 instruction set as defined in the project requirements. It handles various instruction types, including but not limited to:

- Arithmetic operations (`ADD`, `SUB`, `MUL`, `DIV`)
- Logical operations (`AND`, `OR`, `NOT`, `XOR`)
- Branch instructions (`BR`, `BRn`, `BRz`, `BRp`, etc.)
- Control instructions (`JSR`, `JSRR`, `TRAP`, `RTI`)
- Shift operations (`SLL`, `SRL`, `SRA`)
- Memory operations (`LDR`, `STR`)
- Comparison instructions (`CMP`, `CMPU`, `CMPI`, `CMPIU`)

For a detailed list of instructions and their encodings, refer to the LC4 Instruction Set documentation provided in the project.

## Notes

- The program assumes that the object file is well-formed and follows the LC4 object file format.
- Error handling is minimal; invalid instructions or malformed files may lead to unexpected behavior.
- The disassembler currently implements a subset of the instruction set for demonstration purposes. Additional instructions can be added by extending the `reverse_assemble` function.
- Labels are handled according to the symbol sections in the object file. Each label is associated with its corresponding address in the memory linked list.

