#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *str = NULL;
  size_t len = 0;

  while (1) {
    printf("Enter path: ");
    fflush(stdout);

    ssize_t check = getline(&str, &len, stdin);
    if (check == -1) {
      break;
    }

    str[strcspn(str, "\n")] = '\0';
    pid_t pid = fork();

    if (pid) {
      waitpid(pid, NULL, 0);
    } else {
      execl(str, str, NULL);
      perror("error when running exec\n");
      exit(1);
    }
    free(str);
    return 0;
  }
}
