#include <stdio.h>
#include <stdlib.h>

int frobcmp(const void* a, const void* b)
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
    fprintf(stderr, "frobcmp failed");
    exit(1);
  }
}

int main()
{
  int c = getchar();
  if (c == EOF || c == '\0')
    return 0;
  if (c == '\n')
    c = getchar();
  char** arr = malloc(sizeof(char*));
  char* phrase = malloc(sizeof(char));
  int psize = 1;
  int asize = 1;
  if (arr == NULL || phrase == NULL)
  {
    fprintf(stderr, "malloc failed");
    exit(1);
  }
  char prev = '0';
  while (!ferror(stdin))
  {
    if (c == ' ')
    {
      phrase[psize-1] = ' ';
      arr[asize-1] = phrase;
      c = getchar();
      if (c!=EOF) {


      char* nextphrase = (char*) malloc(sizeof(char));
      if (nextphrase != NULL) {
	phrase = nextphrase;
      }
      else {
	fprintf(stderr, "malloc failed");
	exit(1);
      }
      psize = 1;
	asize++;
	char** newarr = (char**)realloc(arr, asize*sizeof(char*));
	if (newarr != NULL)
	  {
	    arr = newarr;
	  }
	else
	  {
	    fprintf(stderr, "realloc failed");
	    exit(1);
	  }
      }
      else {
	break;
      }
    }
    else if (c == EOF)
    {
      if (prev != ' ')
      {
	phrase[psize-1] = ' ';
      }
      arr[asize-1] = phrase;
      break;
      }
    else
    {
      char cchar = c;
      phrase[psize-1] = cchar;
      psize++;
      char* newphrase = realloc(phrase, (psize+1)*sizeof(char));
      if (newphrase != NULL)
      {
        phrase = newphrase;
      }
      else
      {
        fprintf(stderr, "realloc failed");
        exit(1);
      }
      c = getchar();
    }

    prev = c;
  }
  if (ferror(stdin)) {
    fprintf(stderr, "read error");
    exit(1);
  }

  //    printf("arr size: %d\n", asize);

  qsort(arr, asize, sizeof(char*), frobcmp);

  // Output
  size_t i, k;
  for (k = 0; k < asize; k++) {
    for (i = 0; ;i++) {
      char ch = arr[k][i];
      if (ch != ' ')
	putchar(ch);
      else {
	putchar(ch);
	break;
      }
    }
  }

  
  for (k = 0; k < asize; k++){
    if (arr[k]) {
      free(arr[k]);
      arr[k] = NULL;
    }
  }
  if (arr) {
    free(arr);
    arr = NULL;
  }
  return 0;
}
