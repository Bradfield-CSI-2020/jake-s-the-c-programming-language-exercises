/*  Exercise 5-5
    Write versions of the library functions strncpy, strncat, and strncmp, which
    operate on at most the first n characters of their argument strings. For example,
    strncpy(s,t,n) copies at most n characters of t to s.
    Full descriptions are in appendix B.

    (man 3 also)
*/
#include <stdio.h>
#include <stdlib.h>

void strncpy(char *s, char *t, int n) {
  while((n--) > 0 && *t != 0)
    *s++ = *t++;
  *s = 0;
}

int main(int argc, char *argv[]) {
  char result[200];
  strncpy(result, argv[1], atoi(argv[2]));
  printf("%s\n", result);
  return 0;
}