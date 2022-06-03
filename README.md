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

|asm/cpu cmd          |x86 cmd              |x86 bin code|
|:-------------------:|:-------------------:|:----------:|
|end 		      |                     |0xC3        |
|in		      |[in](#in)            |            |
|out                  |[out](#out)          |            |
|sqrt		      |[sqrt](#sqrt)	    |		 |
|                     |                     |            |
|push 5 (number)      |push + num (4 bytes) |0x68 + num  |
|push ax              |push rax             |0x50	 |
|push bx              |push rbx             |0x53	 |
|push cx              |push rcx             |0x51	 |
|push dx              |push rdx             |0x52	 |
|                     |                     |		 |
|pop ax               |pop rax              |0x58	 |
|pop bx               |pop rbx              |0x5B	 |
|pop cx               |pop rcx              |0x59	 |
|pop dx               |pop rdx              |0x5A	 |
|                     |                     |		 |
|add                  |pop rdi              |0x57	 |
|                     |pop rsi              |0x56	 |
|                     |add rdi, rsi         |0x48	 |
|		      |                     |0x01	 |
|                     |              	    |0xF7	 |
|                     |                     |		 |
|sub		      |pop rdi		    |0x57	 |
|		      |pop rsi		    |0x56	 |
|		      |sub rdi, rsi	    |0x48	 |
|		      |			    |0x29        |
|		      |			    |0xF7        |
|		      | 		    |		 |
|mul		      |pop rdx		    |0x5A	 |
|		      |pop rax		    |0x58	 |
|		      |imul		    |0x48	 |
|		      |			    |0xF7	 |
|		      | 		    |0xEA	 |
|		      |			    |		 |
|del		      |pop rcx		    |0x59	 |
|		      |pop rax		    |0x58	 |
|		      |cqo		    |0x48	 |
|		      |			    |0x99	 |
|		      |idiv		    |0x48	 |
|		      |			    |0xF7	 |
|		      |			    |0xF9	 |
|		      |			    |		 |
|call		      |call + addr (4 bytes)|0xE8 + addr |
|ret		      |                     |0xC3	 |
|		      |			    |		 |
|jump		      |jmp + addr (4 bytes) |0xEA + addr |
|jump (condition)     |pop rsi		    |0x56	 |
|		      |pop rdi		    |0x57 	 |
|		      |cmp rdi, rsi	    |0x48	 |
|		      |			    |0x39	 |
|		      |			    |0xF7	 |
|		      |je  + addr (4 bytes) |0x74	 |
|		      |jne + addr (4 bytes) |0x75	 |
|		      |jl  + addr (4 bytes) |0x7C	 |
|		      |jle + addr (4 bytes) |0x7E	 |
|		      |jg  + addr (4 bytes) |0x7F	 |
|		      |jge + addr (4 bytes) |0x7D	 |

### in
```c++
    ++ip_bin;
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
//! mov r10, addr in
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

### out
```c++
    ++ip_bin;

    POP_RDI;

//! mov r10, addr out
    trans->buff[ip++] = 0x41;
    trans->buff[ip++] = 0xBA;

    unsigned long ptr = (unsigned long)out;

    for (size_t index = 0; index < 4; ++index) {
        *(trans->buff + ip + index) = *((char *)&ptr + index);
        // printf ("%X ", *((char *)&ptr + index));

    }
    ip += sizeof (int) / sizeof (char);
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
    CALL_R10;
/////////////////////////////////////////////////
    RESTORE_RAX;
    RESTORE_RBX;
    RESTORE_RCX;
    RESTORE_RDX;
```
### sqrt
```c++

    ++ip_bin;

    POP_RDI;

    trans->buff[ip++] = 0x41;           //mov r10, out(adress)
    trans->buff[ip++] = 0xBA;

    unsigned long ptr = (unsigned long)r_sqrt;

////CHANGE TO INT PTR!!!!!!!!!!!
    for (size_t index = 0; index < 4; ++index) {
        *(trans->buff + ip + index) = *((char *)&ptr + index);
        // printf ("%X ", *((char *)&ptr + index));
    }
    ip += sizeof (int) / sizeof (char);
/////////////////////////////////////////////////
    SAVE_RAX;
    SAVE_RBX;
    SAVE_RCX;
    SAVE_RDX;
/////////////////////////////////////////////////
    CALL_R10;
/////////////////////////////////////////////////
    PUSH_RAX;

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
