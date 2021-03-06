/*  Exercise 5-7
    Rewrite readlines to store lines in an array supplied by main, 
    rather than calling alloc to maintain storage. How much faster
    is the program?
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 50000
#define MAXSTORAGE 100000

char *lineptr[MAXLINES];

int readlines2(char storage[], char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

int main() {
  printf("Write lines, then ctrl + d to print\n");
  int nlines;
  char storage[MAXSTORAGE];
  clock_t start = clock();
  if ((nlines = readlines2(storage, lineptr, MAXLINES)) >= 0) {
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

int readlines2(char storage[], char *lineptr[], int maxlines) {
  int len, nlines;
  char *maxstorage = storage + MAXSTORAGE - MAXLEN;

  nlines = 0;
  while((len = myGetline(storage, MAXLEN)) > 0) {
    lineptr[nlines++] = storage;
    storage[len-1] = 0;
    storage += len;
    if (nlines >= maxlines || storage > maxstorage) {
      return -1;
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