/*  Exercise 5-5
    Write versions of the library functions strncpy, strncat, and strncmp, which
    operate on at most the first n characters of their argument strings. For example,
    strncpy(s,t,n) copies at most n characters of t to s.
    Full descriptions are in appendix B.

    (man 3 also)
*/
#include <stdio.h>
#include <stdlib.h>

// return <0 if s<t, 0 if s == t, >0 if s>t
int strncmp(char *s, char *t, int n) {
  for(; *s == *t && n > 0; n--, s++, t++)
    if (*s == 0) return 0;

  return n == 0 ? 0 : *s - *t;
}

int main(int argc, char *argv[]) {
  printf("%d\n", strncmp(argv[1], argv[2], atoi(argv[3])));
  return 0;
}