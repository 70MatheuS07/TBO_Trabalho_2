CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
OBJS = trab2.o tAresta.o

all: trab2

trab2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o trab2

trab2.o: trab2.c tAresta.h
	$(CC) $(CFLAGS) -c trab2.c

tAresta.o: tAresta.c tAresta.h
	$(CC) $(CFLAGS) -c tAresta.c

clean:
	rm -f $(OBJS) trab2