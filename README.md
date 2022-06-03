# JIT COMPILER

## CONTENTS

[1.INTRO](#INTRO)


[2.USAGE](#USAGE)

[3.COMMANDS LIST](#COMMANDS-LIST)

[4.RUN TIME COMPARASON](#RUN-TIME_COMPARASON)

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

## JIT_INFO

### To look into **my language commands** visit https://github.com/Ropho/CPU

### Comparason between **my asm/cpu cmds and x86**

|asm/cpu cmd          |x86 cmd              |
|:-------------------:|:-------------------:|
|end 		      |0xC3                 |
|in		      |[in](#in)




### in
```c++
    ++ip_bin;
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
//! mov r10, addr
    trans->buff[ip++] = 0x41;
    trans->buff[ip++] = 0xBA;

    unsigned long ptr = (unsigned long) in;

    for (size_t index = 0; index < 4; ++index) {
        *(trans->buff + ip + index) = *((char *) &ptr + index);
    }

    ip += sizeof (int) / sizeof (char);

    SAVE_RSP;
    ALIGN_STACK;

    CALL_R10;
    
    RESTORE_RSP;

    PUSH_RAX;
/////////////////////////////////////////////////
    RESTORE_RAX;
    RESTORE_RBX;
    RESTORE_RCX;
    RESTORE_RDX;


```
## RUN-TIME_COMPARASON

## Measured time table:
|  	     |CPU (own) | JIT   |
|:----------:|:--------:|:-----:|
|real (secs) |0.0065    |0.00008|

> Total Increase: 82 times.
