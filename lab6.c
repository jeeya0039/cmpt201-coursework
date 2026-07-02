#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define ASSERT(expr)                                                                               \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Assertion failed: %s\nFile: %s Line: %d\n", #expr, __FILE__, __LINE__);     \
      exit(1);                                                                                     \
    }                                                                                              \
  }

#define TEST(expr)                                                                                 \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Test failed: %s\n", #expr);                                                 \
      exit(1);                                                                                     \
    } else {                                                                                       \
      printf("Test passed: %s\n", #expr);                                                          \
    }                                                                                              \
  }

typedef struct node {
  uint64_t data;
  struct node *next;
} node_t;

node_t *head1 = NULL;

void insert_sorted_1(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = data;
  new_node->next = NULL;

  if (head1 == NULL || data < head1->data) {
    new_node->next = head1;
    head1 = new_node;
    return;
  }
  node_t *curr = head1;
  while (curr->next != NULL && curr->next->data < data) {
    curr = curr->next;
  }

  new_node->next = curr->next;
  curr->next = new_node;
}

int index_of_1(uint64_t data) {
  node_t *curr = head1;
  int index = 0;

  while (curr != NULL) {
    if (curr->data == data) {
      return index;
    }
    curr = curr->next;
    index++;
  }
  return -1;
}
typedef struct info {
  uint64_t sum;
} info_t;

node_t *head2 = NULL;
info_t info = {0};

void insert_sorted_2(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = data;
  new_node->next = NULL;

  if (head2 == NULL || data < head2->data) {
    new_node->next = head2;
    head2 = new_node;
  } else {
    node_t *curr = head2;

    while (curr->next != NULL && curr->next->data < data) {
      curr = curr->next;
    }
    new_node->next = curr->next;
    curr->next = new_node;
  }

  info.sum += data;
}

uint64_t sum_list(node_t *head) {
  uint64_t sum = 0;

  while (head != NULL) {
    sum += head->data;
    head = head->next;
  }

  return sum;
}

int index_of_2(uint64_t data) {
  node_t *curr = head2;
  int index = 0;

  while (curr != NULL) {
    if (curr->data == data) {
      return index;
    }
    curr = curr->next;
    index++;
  }

  return -1;
}
int main() {
  insert_sorted_1(1);
  insert_sorted_1(2);
  insert_sorted_1(5);
  insert_sorted_1(3);

  TEST(index_of_1(3) == 2);

  insert_sorted_1(0);
  insert_sorted_1(4);

  TEST(index_of_1(4) == 4);
  insert_sorted_2(1);
  insert_sorted_2(3);
  insert_sorted_2(5);
  insert_sorted_2(2);

  TEST(index_of_2(2) == 1);
  ASSERT(info.sum == sum_list(head2));

  return 0;
}
