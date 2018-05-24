#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
int cmp(const void* a, const void* b, int upper)
{
  if (a && b) {
  // compare two char arrays
  const char* charArrA = *(const char**)a;
  const char* charArrB = *(const char**)b;

  while ((*charArrA) != ' ' && (*charArrB) != ' ')
  {
    // decode each char
    char ca = (*charArrA)^42;
    char cb = (*charArrB)^42;

    if (upper) {
      if (ca >= -1 && ca <= UCHAR_MAX)
	ca = toupper(ca);
      if (cb >= -1 && cb <= UCHAR_MAX)
        cb = toupper(cb);
    }
    
    if (ca > cb)
      return 1;
    else if (ca < cb)
      return -1;
    else
    {
      charArrA++;
      charArrB++;
    }
  }

  // if A ends earlier than B
  if ((*charArrA) == ' ' && (*charArrB) != ' ')
    return -1;
  // if B enes earlier than A
  else if ((*charArrB) == ' ' && (*charArrA) != ' ')
    return 1;
  // if they are the same
  else return 0;
  }
  else {
    write(2, "frobcmp failed\n", 15);
    exit(1);
  }
}


int frobcmpu(const void* a, const void* b)
{
  return cmp(a, b, 1);
}
int frobcmp(const void* a, const void* b)
{
  return cmp(a, b, 0);
}


int main(int argc, char **argv)
{
  struct stat buf;
  int f = fstat(0,&buf);
  int size = buf.st_size;
  if (size < 0) {
    write(2, "fstat failed\n",13);
    exit(1);
  }
  
  //  printf("size: %d\n", size);

  char* text = malloc(size*sizeof(char));

  int upper = 0;
  if (argc > 2) {
    write(2, "#arg error\n", 11);
    exit(1);
  }
  else if (argc == 2) {
    if (strcmp(argv[1], "-f") == 0) {
      upper = 1;
    }
    else {
      write(2, "wrong arg\n", 10);
      exit(1);
    }
  }

  //printf("file size: %d\n", size);
  
  int it = 0;
  int c = 0;
  int bytes = read(0, &c, 1);
  if (bytes == 0)
    return 0;
  while (1) {
    if (bytes == 0) {
      break;
    }
    if (!S_ISREG(0) && it >= size) {
      size++;
      char* newarr = realloc(text, size*sizeof(char));
      if (!newarr) {
        write(2, "realloc failed\n", 15);
        exit(1);
      }
      text = newarr;
    }
    text[it] = c;
    it++;
    bytes = read(0, &c, 1);
  }

  //printf("%s", text);

  if (text[size-1] != ' ') {
    size++;
    char* newarr = realloc(text, size*sizeof(char));
    if (!newarr) {
      write(2, "realloc failed\n", 15);
      exit(1);
    }
    text = newarr;
    text[size-1] = ' ';
  }
  int nPhrases = 0;
  for (size_t i = 0; i < size; i++) {
    if (text[i] == ' ')
      nPhrases++;
  }

  //  printf("\n%d phrases\n", nPhrases);

  char** arr = malloc(nPhrases*sizeof(char*));
  if (!arr) {
    write(2, "malloc failed\n", 14);
    exit(1);
  }

  
  arr[0] = &(text[0]);
  size_t asize = 1;
  for (size_t i = 0; i < size-1; i++) {
    if (text[i] == ' ')
      arr[asize++] = &(text[i+1]);
  }

  if (!upper)
    qsort(arr, asize, sizeof(char*), frobcmp);
  else
    qsort(arr, asize, sizeof(char*), frobcmpu);


  for (size_t i = 0; i < asize; i++) {
    for (size_t j = 0; ; j++) {
      char ch = arr[i][j];
      if (ch == ' ') {
	write(1, &ch, 1);
	break;
      }
      else
	write(1, &ch, 1);
    }
  }
  
  if (text) {
    free(text);
    text = NULL;
  }

  if (arr) {
    free(arr);
    arr = NULL;
  }
}
