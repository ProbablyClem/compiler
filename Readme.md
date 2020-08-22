# ROO
## Rust Object Oriented
 * Rust like syntax
 * Static typing
 * Made for OO
 * Borrow checker 

## Requirement
 * Linux
 * lcc (LLVM)
 * gcc

## Installation
Clone the repos</br>
build with `make` </Br>

## usage
```
$./roo input_file
```
input_file file being the file to compile. </br>
Then run
```
$./run.sh
```
to compile the llvm file into an executable and launch it.
The output will be ./a.out

# Compiler Architecture
## Lexer
### scan.c</br>
Convert the code into token. </br>
Throw an error if the lexer don't recognize the input.

## Parser
### expr.c</br>
Generate an AST from the tokens.</br>
The tree is generated with the token's priority found in `OpPrec[]`. </br>
Thrown an error if the input does't respect the grammar.
### tree.c
Utils for generating AST nodes.

### stmt.c
Functions trees from statements such as functions or loops.

### misc.c
Utils requesting token such as colon().

### types.c
Functions managing types compatibilities.

## LLVM generator
### gen.c

Generate llvm ir code from the AST.</br>

### cg.c
Utils for generating llvm code.

## Other
### main.c
[Entry]</br>
Open and close files and calls other files?

### data.h
Expose global variables.

### decl.h
Expose public functions.

### defs.h
Public Enums

### delc.c
Utils for declaring variables or functions.

### sym.c
Functions managing the symbols tables.


# Ressources
Compiler tutorial : https://github.com/DoctorWkt/acwj </br>
LLVM IR doc : http://llvm.org/docs/LangRef.html </br>
LLVM IR unofficial guide : https://mapping-high-level-constructs-to-llvm-ir.readthedocs.io/en/latest/README.html </br>