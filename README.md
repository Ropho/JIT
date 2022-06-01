# JIT COMPILER

## CONTENTS

[1.INTRO](#INTRO)


[2.USAGE](#USAGE)

[3.JIT INFO](#JIT)

[4.RUN TIME COMPARASON](#RUN)

## INTRO

Tasks of this project were: 
1. To make a binary translator from **my language** into **x86** architecture.
2. To compare run-time between **JIT-compiler (binary translator) and my own proceccor** 



## USAGE

### Compile
		all:
	gcc -g -masm=intel main.cpp func.cpp std_func.cpp -DNDEBUG -no-pie -lm -o main	


### OPTIONS

1.  Processor
    > AMD Ryzen 5 4500U
2.  Language
    > C, C++
3.  Profiler
    > Kcachegrind (WSL)
4.  Compiler
    > GCC
5.  Timer
    + time ./program (WSL)
    + total instruction fetch cost (kcachegrind)

## JIT INFO:

### To look into **my language commands** visit https://github.com/Ropho/lang



## RUN TIME COMPRARASON
