CC = gcc
CCFLAGS = -Wall -Werror -pedantic -O3
CFILES = main.c crypto.c
HFILES = crypto.h
CTESTFILES = crypto.c testCrypto.c

.PHONY: all clean debug test

all: encryption decryption
debug: CCFLAGS += -g
debug: encryption decryption

clean:
	rm -f *.o *.exe

test: $(CTESTFILES)
	$(CC) -o test $^

encryption: $(CFILES)
	$(CC) -o encrypt $(CCFLAGS) $^

decryption: $(CFILES)
	$(CC) -o decrypt $(CCFLAGS) $^