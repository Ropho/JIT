all:
	gcc -g -masm=intel main.cpp func.cpp -no-pie -o main