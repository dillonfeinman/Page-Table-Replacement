CFLAGS = -Wall -g -Wextra -DDebug
P = prog3Feinman_dfeinma1

all: prog3

prog3: $(P).cpp
	g++ -c $(P).cpp
	g++ -g $(P).o -o $(P)
clean:
	rm -rf *.o $(P) *.csv *.png
run: all
	./$(P)
checkmem: all
	valgrind -v --leak-check=full --track-origins=yes ./$(P)

plots: plot_hit_rates.plt
	g++ -c $(P).cpp
	g++ -g $(P).o -o $(P)
	./$(P) 100 10000
	gnuplot -e "title='No Locality'" -e "input_filename='no_locality.csv'" plot_hit_rates.plt > no_locality.png
	gnuplot -e "title='80-20'" -e "input_filename='80-20.csv'" plot_hit_rates.plt > 80-20.png
	gnuplot -e "title='Looping'" -e "input_filename='looping.csv'" plot_hit_rates.plt > looping.png
