CC = clang
CFLAGS = -Wall -Wextra -std=c11 -g

all: build 

build: trie.o
	@$(CC) $(CFLAGS) -c trie.c

link: trie.o
	@$(CC) $(CFLAGS) -o trie trie.o

run: build link
	./trie


.PHONY: clean

clean:
	$(RM) -f *.o
