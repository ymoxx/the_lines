CC = gcc
CFLAGS = -Ofast -march=native

all: l1 l2

l1: l1.o lines.o
l2: l2.o lines.o

l1.o l2.o: lines.h

clean:
	rm -f l1 l2 *.o