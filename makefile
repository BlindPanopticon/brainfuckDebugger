program : main.o brainfuck.o
	g++ -g -o program main.o brainfuck.o
main.o : main.cpp
	g++ -g -c main.cpp
brainfuck.o : brainfuck.cpp brainfuck.h
	g++ -g -c brainfuck.cpp brainfuck.h
clean :
	rm program main.o brainfuck.o
