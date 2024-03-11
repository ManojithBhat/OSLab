# OSLab
###Aim :  
The objective of this project is to design and implement a two-pass assembler in C language which converts assembly language code into machine code. 

###Theory:
Two pass Assembler utilizes two stage process to convert assembly language to machine code 
####First Pass:
Defines symbols and literals and remembers them in symbolic table form and literal table form respectively. Keep track of location counter. Process pseudo-operations.
####Pass-2:
Generate object code by converting symbolic op-code into corresponding numeric op-code.
Generate data for literals and look for values of symbols.

One-pass assembler cannot resolve issues of forward references of data symbols. It requires all data symbols to be defined before they are being used. A Two-pass assembler solves this confusion by devoting one pass exclusively to resolve all issues of forward referencing and then generates object code with no chaos in the next pass.

###Input: 
Assembly code:  provide the assembly code as input for conversion to machine code.
Op- instruction code : contains binary representation of the opcode present in the assembly code 

###Output: 
Symbol Table :The assembler will create a symbol table during the first pass.
Intermediate code: a representation of the source code after the first pass. It includes opcode and operand information.
This code serves as an intermediate step between the source code and the final object code.
The intermediate code is saved and used in the second pass to generate the object code.
Assembly Code: The assembler will generate the corresponding assembly code after successfully completing the two passes through the provided machine code opcodes.
