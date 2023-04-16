#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Node {
  struct Node *children[ALPHABET_SIZE];
  bool isWord;
  bool isLeaf;
};

struct Node *new_node() {
  struct Node *result = malloc(sizeof *result);

  if (!result)
    return NULL;

  result->isWord = false;

  return result;
}

struct Trie {
  struct Node root;
  int wordCount;
};

struct Trie *new_trie() {
  struct Trie *result = malloc(sizeof *result);

  if (!result)
    return NULL;

  result->wordCount = 0;

  return result;
}

bool trie_add_word(struct Trie *trie, char const *word) {

  struct Node *cur = &trie->root;
  bool shouldBeLeaf = false;

  for (char const *i = word; *i != '\0'; i++) {
    char const c = *i;
    int index = c - 'a';

    shouldBeLeaf = false;
    if (!(cur->children[index])) {
      shouldBeLeaf = true;
      cur->children[index] = new_node();
    }

    cur = cur->children[index];

    if (!cur)
      break;
  }
  cur->isLeaf = shouldBeLeaf;
  cur->isWord = true;

  return true;
}

void print_trie_dfs(struct Node *cur, char *BUF, int depth) {

  if (cur->isLeaf || cur->isWord) {
    BUF[depth] = '\0';
    printf("%s (%d)\n", BUF, depth);
  }

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if ((cur->children[i])) {
      BUF[depth] = (i + 'a');
      print_trie_dfs(cur->children[i], BUF, depth + 1);
    }
  }
}

void print_trie(struct Trie *trie) {
  struct Node *root = &(trie->root);
  char BUF[1000];
  memset(BUF, 0, sizeof(BUF));

  print_trie_dfs(root, BUF, 0);
}

char *read_file(char *fileName) {
  FILE *file = fopen(fileName, "r");

  if (!file)
    return false;

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  // Allocate string for every single item in file
  char *buffer = malloc(sizeof *buffer * (size + 1));
  printf("Allocating: %d bytes\n", size + 1);

  int read_size = fread(buffer, sizeof(char), size, file);
  buffer[size] = '\0';

  if (size != read_size) {
    free(buffer);
    return NULL;
  }

  return buffer;
}

int main(int argc, char const *argv[]) {

  char *buffer = read_file("words.txt");
  printf(buffer ? "SUCCESS" : "FAILURE\n\n");

  struct Trie *trie = new_trie();

  char *wordStart = buffer;
  for (char *i = buffer; *i != '\0'; i++) {

    if (*i != '\n')
      continue;

    *i = '\0';
    int length = (i - wordStart);
    printf("Adding word: %s (%d)\n", wordStart, length);
    trie_add_word(trie, wordStart);
    wordStart = i + 1;
  }

  trie_add_word(trie, "hello");
  trie_add_word(trie, "helicopter");
  trie_add_word(trie, "hell");
  trie_add_word(trie, "everyone");
  trie_add_word(trie, "is");
  trie_add_word(trie, "nice");
  trie_add_word(trie, "niceties");
  trie_add_word(trie, "niceness");
  trie_add_word(trie, "alphabetical");
  trie_add_word(trie, "order");
  trie_add_word(trie, "possibly");

  // Add command line arguments
  // printf("Adding command line arguments:\n");
  // for (int i = 1; i < argc; i++) {
  //   printf("%s", argv[i]);
  //   if (i != argc - 1)
  //     printf(", ");
  //   trie_add_word(trie, argv[i]);
  // }

  print_trie(trie);
}
