#include <stdio.h>
#include <string.h>
#define MAX_LINES 5
#define MAX_LENGTH 1024

int main(void) {
  char lines[MAX_LINES][MAX_LENGTH];
  char input[MAX_LENGTH];
  int next = 0;
  int count = 0;

  while (1) {
    printf("Enter input: ");
    fflush(stdout);
    if (fgets(input, sizeof(input), stdin) == NULL) {
      break;
    }
    input[strcspn(input, "\n")] = '\0';
    strcpy(lines[next], input);
    next = (next + 1) % MAX_LINES;

    if (count < MAX_LINES) {
      count++;
    }
    if (strcmp(input, "print") == 0) {
      int start = (next - count + MAX_LINES) % MAX_LINES;

      for (int i = 0; i < count; i++) {
        int index = (start + i) % MAX_LINES;
        printf("%s\n", lines[index]);
      }
    }
  }
  return 0;
}
