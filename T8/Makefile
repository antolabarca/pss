CFLAGS= -g -Wall -pedantic -std=c99
LDFLAGS= -g

all: test-t8

test-t8.o t8.o: maleta.h

test-t8: t8.o test-t8.o

clean:
	rm -f *.o
	rm -f test-t8
