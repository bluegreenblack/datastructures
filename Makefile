
# Write a Makefile to build trie.c and trie.h into a library called libtrie.a

CC = clang
CFLAGS = -Wall -Wextra -std=c11 -g

all: build 

build: trie.o
	@$(CC) $(CFLAGS) -c trie.c

link: trie.o
	@$(CC) $(CFLAGS) -o trie trie.o

run: build link
	./trie

clean:
	rm -f *.o

# Path: trie.c

