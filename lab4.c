#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
}


int main() {
  void *heap_start = sbrk(256);

  if (heap_start == (void *)-1) {
    perror("sbrk");
    return 1;
  }

  const size_t BLOCK_SIZE = 128;

  char *first_block = (char *)heap_start;
  char *second_block = first_block + BLOCK_SIZE;

  struct header *h1 = (struct header *)first_block;
  struct header *h2 = (struct header *)second_block;

  h1->size = BLOCK_SIZE;
  h1->next = NULL;

  h2->size = BLOCK_SIZE;
  h2->next = h1;

  char *data1 = first_block + sizeof(struct header);
  char *data2 = second_block + sizeof(struct header);

  size_t data_size = BLOCK_SIZE - sizeof(struct header);

  memset(data1, 0, data_size);
  memset(data2, 1, data_size);

  printf("first block:      %p\n", (void *)first_block);
  printf("second block:     %p\n", (void *)second_block);

  printf("first block size: %lu\n", h1->size);
  printf("first block next: %p\n", (void *)h1->next);

  printf("second block size: %lu\n", h2->size);
  printf("second block next: %p\n", (void *)h2->next);

  for (size_t i = 0; i < data_size; i++) {
    printf("%d\n", data1[i]);
  }

  for (size_t i = 0; i < data_size; i++) {
    printf("%d\n", data2[i]);
  }

  return 0;
}
