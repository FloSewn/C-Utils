CC = gcc
CFLAGS = -Wall -g -pedantic -DNDEBUG
 
.PHONY: clean all

BINARY=run_test

all: main

main: main.o bstrlib.o
	$(CC) $(CFLAGS) obj/main.o obj/bstrlib.o -o ${BINARY} $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	mv main.o obj/.

bstrlib.o: src/extern/bstrlib.c
	$(CC) $(CFLAGS) -c src/extern/bstrlib.c
	mv bstrlib.o obj/.

clean:
	rm -f ${BINARY}
	rm -f *.o 
