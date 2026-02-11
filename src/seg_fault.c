#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void segfault_handler(int sig) {
  printf("Congratulations! You overflowed the buffer");
  exit(0);
}

void vulnerable() {
  char buffer[8];
  printf("Enter input: ");
  gets(buffer);
}

int main() {
  signal(SIGSEGV, segfault_handler);

  printf("Overflow the buffer to win!\n");
  vulnerable();

  printf("No segfault yet...\n");
  return 0;
}
