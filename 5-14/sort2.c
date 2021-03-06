/*  Exercise 5-14
    Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing)
    order. Be sure that -r works with -n.
*/

#include <stdio.h>
#include <string.h>
#include "numcmp.c"
#include "readlines.c"

#define MAXLINES 5000                       /* max #lines to be sorted */
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void myQsort(void *lineptr[], int left, int right,
  int (*comp)(void *, void *));

int numcmp(char *, char *);
int reversed(void *, void *);

int (*basesortfn)(void *, void *);

/* sort input lines */
int main(int argc, char * argv[]) {
  int nlines;                               /* number of input lines read */
  int numeric = 0;                          /* 1 if numeric sort */
  int reverse = 0;                          /* 2 if reverse sort */
  int (*sortfn)(void *, void *);

  for(int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "-n") == 0) {
      numeric = 1;
    }
    if(strcmp(argv[i], "-r") == 0) {
      reverse = 1;
    }
  }

  basesortfn = numeric ? (int (*)(void *, void *))numcmp : (int (*)(void *, void *))strcmp;
  sortfn = reverse ? reversed : basesortfn;

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    myQsort((void **) lineptr, 0, nlines-1, sortfn);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* myQsort: sort v[left]...v[right] into increasing order */
void myQsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int i, last;
  void swap(void *v[], int, int);

  if (left >= right)                        /* do nothing if array contains */
    return;                                 /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  myQsort(v, left, last - 1, comp);
  myQsort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j) {
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int reversed(void * a, void * b) {
  return (*basesortfn)(b, a);
}