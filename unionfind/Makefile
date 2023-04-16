CC = clang
CFLAGS = -Wall -Wextra -std=c11 -g

all: build link

%: %.c
	$(CC) $(CFLAGS) $< -o $@

build: uf.o
	@$(CC) $(CFLAGS) -c uf.c

link: uf.o
	@$(CC) $(CFLAGS) -o uf uf.o

run: build link
	./uf


.PHONY: clean

clean:
	$(RM) -f *.o

