#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define EXTRA_SIZE 256
#define BLOCK_SIZE 128
#define BUF_SIZE 100

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main(void) {
  void *heap_start = sbrk(EXTRA_SIZE);
  if (heap_start == (void *)-1) {
    handle_error("sbrk");
  }
  struct header *first_block = (struct header *)heap_start;
  struct header *second_block = (struct header *)((char *)heap_start + BLOCK_SIZE);
  first_block->size = BLOCK_SIZE;
  first_block->next = NULL;
  second_block->size = BLOCK_SIZE;
  second_block->next = first_block;
  unsigned char *first_data = (unsigned char *)(first_block + 1);
  unsigned char *second_data = (unsigned char *)(second_block + 1);
  size_t data_size = BLOCK_SIZE - sizeof(struct header);
  for (size_t i = 0; i < data_size; i++) {
    first_data[i] = 0;
    second_data[i] = 1;
  }
  print_out("first block:       %p\n", &first_block, sizeof(first_block));
  print_out("second block:      %p\n", &second_block, sizeof(second_block));
  print_out("first block size:  %lu\n", &first_block->size, sizeof(uint64_t));

  print_out("first block next:  %p\n", &first_block->next, sizeof(first_block->next));

  print_out("second block size: %lu\n", &second_block->size, sizeof(uint64_t));
  print_out("second block next: %p\n", &second_block->next, sizeof(second_block->next));
  for (size_t i = 0; i < data_size; i++) {
    char buf[20];
    int len = snprintf(buf, sizeof(buf), "%u\n", first_data[i]);
    write(STDOUT_FILENO, buf, len);
  }

  for (size_t i = 0; i < data_size; i++) {
    char buf[20];
    int len = snprintf(buf, sizeof(buf), "%u\n", second_data[i]);
    write(STDOUT_FILENO, buf, len);
  }
  return 0;
}
