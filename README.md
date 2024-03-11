# OSLab
### Aim :  
To implement a Two-Pass assembler which takes a Machine-operation code file and an assembly level instruction file as a input and after execution, the binary code for each introduction and the information about labels are writtent in machine code file and symbol table file respectively.

### Theory:
### Introduction
Assembler is a program for converting instructions that are written in low-level assembly code into relocatable machine code and generating information along, for the loader.An assembler acts as a bridge between the high-level abstraction of assembly language and the binary machine code that a computer's central processing unit (CPU) can understand. The two-pass approach is a methodology employed in assemblers to efficiently process assembly code and generate corresponding machine code.

### Single Pass Assembler
An assembler that generates the object code directly in memory for immediate execution. It passes through the source code only once and generates instructions by evaluating the mnemonics in operation field and finds the value of symbol and literals to produce machine code.

Two pass Assembler utilizes two stage process to convert assembly language to machine code 
#### First Pass:
Defines symbols and literals and remembers them in symbolic table form and literal table form respectively. Keep track of location counter. Process pseudo-operations.
#### Pass-2:
Generate object code by converting symbolic op-code into corresponding numeric op-code.
Generate data for literals and look for values of symbols.

One-pass assembler cannot resolve issues of forward references of data symbols. It requires all data symbols to be defined before they are being used. A Two-pass assembler solves this confusion by devoting one pass exclusively to resolve all issues of forward referencing and then generates object code with no chaos in the next pass.

### Input: 
Assembly code:  provide the assembly code as input for conversion to machine code.
Op- instruction code : contains binary representation of the opcode present in the assembly code 

### Output: 
Symbol Table :The assembler will create a symbol table during the first pass.
Intermediate code: a representation of the source code after the first pass. It includes opcode and operand information.
This code serves as an intermediate step between the source code and the final object code.
The intermediate code is saved and used in the second pass to generate the object code.
Assembly Code: The assembler will generate the corresponding assembly code after successfully completing the two passes through the provided machine code opcodes.
