#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
  char *buffer = NULL;
  size_t bufsize = 0;
  ssize_t chars_read;
  while (1) {
    printf("Enter text: ");
    chars_read = getline(&buffer, &bufsize, stdin);
    if (chars_read == -1) {
      perror("getline failed");
      free(buffer);
      exit(EXIT_FAILURE);
    }

    if (chars_read == 1) {
      break;
    }
    buffer[chars_read - 1] = '\0';
    printf("Tokens:\n");
    char *token;
    char *saveptr;

    token = strtok_r(buffer, " ", &saveptr);
    while (token != NULL) {
      printf(" %s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }
  free(buffer);
  return (0);
}
