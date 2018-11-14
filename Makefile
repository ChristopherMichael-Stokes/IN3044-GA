CC=gcc
CFLAGS=-I. -lm -std=c99
DEPS = foxhole.h ga.h
OBJ = ga_dec.o foxhole.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
