# ProLang Compiler

A mini-compiler for a pedagogical programming language, built with Flex, Bison, and C. This project demonstrates all the classic phases of compilation: lexical analysis, syntax analysis, semantic analysis, symbol table management, and intermediate code generation (quadruplets).

## Features
- **Lexical Analysis**: Tokenization using Flex (`lexical.l`).
- **Syntax Analysis**: LALR(1) grammar with Bison (`syntax.y`).
- **Semantic Analysis**: Type checking, double declaration, constant immutability, array bounds, etc.
- **Symbol Table**: Efficient hash table with chaining for identifiers, constants, keywords, and separators (`TS.h`, `TS.c`).
- **Intermediate Code Generation**: Quadruplet-based IR for assignments and control flow (`quad.h`).
- **Error Reporting**: Precise line/column error messages for syntax and semantic errors.

## Project Structure

```
src/
├── commande.bat         # Build script (compiles and runs the project)
├── lexical.l            # Flex lexer: tokenizes the source code
├── syntax.y             # Bison parser: grammar, semantic actions, code generation
├── TS.h / TS.c          # Symbol table (hash table + routines)
├── quad.h               # Quadruplet structure and routines (IR)
├── source.txt           # Example source program (ProLang)
├── README.md            # This file
```

## How to Build & Run
1. **Install Flex, Bison, and GCC** (if not already):
   ```sh
   sudo apt-get install flex bison gcc
   ```
2. **Compile and run**:
   ```sh
   cd src
   ./commande.bat
   ```
   This will generate the parser, lexer, compile everything, and run the compiler on `source.txt`.

## Output
- **Symbol Table**: Printed after parsing, showing all identifiers, constants, keywords, and separators.
- **Quadruplets**: Intermediate code for assignments and control flow (e.g., IF/ELSE) is displayed.
- **Errors**: Any syntax or semantic errors are reported with line and column numbers.

## Example Language Features
- Variable and constant declarations
- Arithmetic and assignment
- IF/ELSE, WHILE, FOR loops
- Input/Output
- Arrays (with bounds checking)

## Future Enhancements
- [ ] **Expression Evaluation**: Generate temporaries for expressions in quadruplets
- [ ] **While/For Quadruplets**: Add IR for loops and more control structures
- [ ] **Code Optimization**: Dead code elimination, constant folding, etc.
- [ ] **Assembly Code Generation**: Translate quadruplets to x86/MIPS/ARM
- [ ] **Function/Procedure Support**: Add user-defined functions
- [ ] **Better Error Recovery**: Continue parsing after errors
- [ ] **Unit Tests**: Add automated tests for all modules

## Authors
- Lounas 
---
*This project is for educational purposes and demonstrates a full compilation pipeline for a simple language.*
