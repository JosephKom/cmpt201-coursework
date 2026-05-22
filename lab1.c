#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *str = NULL;
  size_t buf = 0;
  char *tok;
  char *saveptr;

  printf("Enter a string to tokenize: ");

  ssize_t check = getline(&str, &buf, stdin);

  if (check != -1) {
    tok = strtok_r(str, " ", &saveptr);
  } else {
    perror("Invalid getline");
    exit(1);
  }

  printf("Tokens:\n");
  while (tok != NULL) {
    printf("%s\n", tok);
    tok = strtok_r(NULL, " ", &saveptr);
  }

  free(str);

  return 0;
}
