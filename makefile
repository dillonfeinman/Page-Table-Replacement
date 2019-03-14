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
plots: plot_hit_rates.plt
	g++ -c prog3sim.cpp
	g++ -g prog3sim.o -o prog3sim
	./$(P) 100 1000
	gnuplot -e "title='No Locality'" -e "input_filename='no_locality.csv'" plot_hit_rates.plt > no_locality.png
	gnuplot -e "title='80-20'" -e "input_filename='80-20.csv'" plot_hit_rates.plt > 80-20.png
	gnuplot -e "title='Looping'" -e "input_filename='Looping.csv'" plot_hit_rates.plt > looping.png
