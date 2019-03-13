CFLAGS = -Wall -g -Wextra -DDebug
P = prog3sim

all: prog3sim

prog3sim: $(P).cpp
	g++ -c prog3sim.cpp
	g++ -g prog3sim.o -o prog3sim


clean:
	rm -rf *.o $(P) *.csv *.png
run: all
	./$(P)
checkmem: all
	valgrind -v --leak-check=full --track-origins=yes ./$(P)
