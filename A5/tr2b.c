#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int length(char *a) {
  int length = 0;
  for (size_t j = 0; a[j] != '\0'; j++)
    length++;
  return length;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "wrong number of arguments\n");
    exit(1);
  }
  
  char* from = argv[1];
  char* to = argv[2];

  if (length(from) != length(to)) {
    fprintf(stderr, "length error\n");
    exit(1);
  }

  int len = length(from);
  for (size_t i = 0; i < len; i++) {
    for (size_t j = i+1; j < len; j++) {
      if (from[i] == from[j]) {
	fprintf(stderr, "duplicate bytes\n");
	exit(1);
      }
    }
  }


  while (!ferror(stdin)) {
    int c = getchar();
    if (c == EOF)
      break;
    for (size_t i = 0; i < len; i++) {
      if (c == from[i]) {
	c = to[i];
	break;
      }
    }
    putchar(c);
  }
  return 0;
}
