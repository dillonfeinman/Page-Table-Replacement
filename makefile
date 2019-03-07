CFLAGS = -Wall
P = prog1sorter
O = prog1generator

all: $(P)

sort: $(P)
	$(P): $(P).o
		gcc $(CFLAGS) $(P).o -o $(P)
	$(P).o: $(P).c
		gcc $(CFLAGS) -c $(P).c -o $(P).o
gen: $(O)
	$(O): $(O).o
		gcc $(CFLAGS) $(O).o -o $(O)
	$(O).o: $(O).c
		gcc $(CFLAGS) -c $(O).c -o $(O).o
clean:
	rm -rf *.o $(P) $(O)
run: all
	./$(P)
checkmem: all
	valgrind -v --leak-check=full --track-origins=yes ./$(P)
