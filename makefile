CFLAGS = -Wall -g -Wextra -DDebug
P = prog3sim

all: prog3sim.o 
	gcc -g prog3sim.o -o prog3sim

prog3sim.o:
	gcc -c prog3sim.cpp

clean:
	rm -rf *.o $(P)
run: all
	./$(P)
checkmem: all
	valgrind -v --leak-check=full --track-origins=yes ./$(P)
