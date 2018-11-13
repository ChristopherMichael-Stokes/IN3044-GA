CC=gcc
CFLAGS=-I. -lm -std=c99
DEPS = foxhole.h ga.h
OBJ = main.o foxhole.o ga_dec.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
