all: prog2

prog1: prog2.o
	g++ prog2.o -g -o prog2

clean:
	rm prog2.o prog2
