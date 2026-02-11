#include <stdio.h>
#include <stdlib.h>

void remove_in_prod() { system("/bin/sh"); }

void username() {
  char buffer[64];

  printf("Enter your name: ");
  gets(buffer);

  printf("Hello, %s!\n", buffer);
}

int main() {
  printf("I hope I execute without any problems!\n");
  username();
  printf("Program completed normally.\n");
  return 0;
}
