CC = gcc
CCFLAGS = -Wall 

.PHONY: all clean

all: cryption
debug: CCFLAGS += -g
debug: cryption

clean: 
	rm -f *.o *.exe

cryption: crypto
	$(CC) -o $(CCFLAGS) $^
