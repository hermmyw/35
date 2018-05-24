#include <stdlib.h>
#include <unistd.h>

int length(char *a) {
  int length = 0;
  for (size_t j = 0; a[j] != '\0'; j++)
    length++;
  return length;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    write(2, "wrong number of arguments\n", 26);
    exit(1);
  }
  
  char* from = argv[1];
  char* to = argv[2];

  if (length(from) != length(to)) {
    write(2, "length error\n", 13);
    exit(1);
  }

  int len = length(from);
  for (size_t i = 0; i < len; i++) {
    for (size_t j = i+1; j < len; j++) {
      if (from[i] == from[j]) {
	write(2, "duplicate bytes\n", 16);
	exit(1);
      }
    }
  }


  while (1) {
    int c = 0;
    int bytes = read(0, &c, 1);
    if (bytes == 0) {
      break;
    }
    for (size_t i = 0; i < len; i++) {
      if (c == from[i])
	c = to[i];
    }
    write(1, &c, 1);
  }
  return 0;
}
