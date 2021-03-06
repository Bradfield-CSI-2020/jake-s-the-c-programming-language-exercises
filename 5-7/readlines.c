/*  Exercise 5-7
    Rewrite readlines to store lines in an array supplied by main, 
    rather than calling alloc to maintain storage. How much faster
    is the program?
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 50000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

int main() {
  printf("Write lines, then ctrl + d to print\n");
  int nlines;

  clock_t start = clock();
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    writelines(lineptr, nlines);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);
    return 0;
  } else {
    printf("error: input too big to sort \n");
    return 1;
  }
}

#define MAXLEN 1000
int myGetline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while((len = myGetline(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = alloc(len)) == NULL) {
      return -1;
    } else {
      line[len-1] = 0;
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  while(nlines--) {
    printf("%s\n", *lineptr++);
  }
}

int myGetline(char *s, int lim) {
  int c, i;
  for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    s[i] = c;
  }
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

#define ALLOCSIZE 100000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

// return pointer to n characters
// return 0 if not able
char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    /*  pointer arithmetic
        allocbuf + ALLOCSIZE = allocbuf[ALLOCSIZE]
          Adding pointer + integer results in a pointer offset by integer.
        (allocbuf + ALLOCSIZE) - allocp = number of elements from the max to current pointer (integer)
          Subtracting a pointer - pointer results in an integer, if they are in the same array.
    */
    allocp += n;
    return allocp - n;
  } else {
    return 0;
  }
}

