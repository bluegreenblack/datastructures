#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}

struct UnionFind {
  int size;
  int *elements;
  int *sizes;
};

struct UnionFind *new_union_find(int size) {

  struct UnionFind *result = malloc(sizeof *result);
  if (!result)
    return NULL;

  result->size = size;
  result->elements = malloc(sizeof *result->elements * size);
  result->sizes = malloc(sizeof *result->sizes * size);

  for (int i = 1; i <= size; i++) {
    result->elements[i - 1] = i;
    result->sizes[i - 1] = 1;
  }

  return result;
}

void destroy_union_find(struct UnionFind *uf) {
  free(uf->elements);
  free(uf->sizes);
  free(uf);
}

int find(struct UnionFind *uf, int a) {
  while (a != uf->elements[a]) {
    a = uf->elements[a];
  }
  return a;
}

bool connected(struct UnionFind *uf, int a, int b) {
  return find(uf, a) == find(uf, b);
}

void unite(struct UnionFind *uf, int a, int b) {
  a = find(uf, a);
  b = find(uf, b);
  if (uf->sizes[a - 1] < uf->sizes[b - 1]) {
    swap(&a, &b);
  }
  uf->sizes[a - 1] += uf->sizes[b - 1];
  uf->elements[b - 1] = a;
}

int main(int argc, char *argv[]) {
  // Added this to remove clang warnings
  for (int i = 1; i < argc; i++)
    printf("%s\n", argv[i]);

  struct UnionFind *uf = new_union_find(100);
  printf("Created UnionFind\n");

  destroy_union_find(uf);
}
