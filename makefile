all:
	gcc -g -masm=intel jit/main.cpp jit/func.cpp jit/std_func.cpp -DNDEBUG -no-pie -lm -o main