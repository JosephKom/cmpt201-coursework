#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addHistory(char *history[], int *count, int *nextIndex, char *line) {
  if (*count == 5) {
    free(history[*nextIndex]);

  } else {
    (*count)++;
  }

  history[*nextIndex] = line;
  *nextIndex = (*nextIndex + 1) % 5;
}

void printHistory(char *history[], int count, int nextIndex) {
  int start;

  if (count < 5) {
    start = 0;

  } else {
    start = nextIndex;
  }

  for (int i = 0; i < count; i++) {
    int index = (start + i) % 5;
    printf("%s\n", history[index]);
  }
}

void cleanupHistory(char *history[], int count) {
  for (int i = 0; i < count; i++) {
    free(history[i]);
  }
}

int main() {
  char *history[5] = {NULL};
  int count = 0;
  int nextIndex = 0;

  while (1) {
    char *line = NULL;
    size_t len = 0;

    printf("Enter input: ");

    if (getline(&line, &len, stdin) == -1) {
      free(line);
      break;
    }

    line[strcspn(line, "\n")] = '\0';

    addHistory(history, &count, &nextIndex, line);

    if (strcmp(line, "print") == 0) {
      printHistory(history, count, nextIndex);
    }
  }
  cleanupHistory(history, count);

  return 0;
}
