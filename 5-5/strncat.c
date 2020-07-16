/*  Exercise 5-5
    Write versions of the library functions strncpy, strncat, and strncmp, which
    operate on at most the first n characters of their argument strings. For example,
    strncpy(s,t,n) copies at most n characters of t to s.
    Full descriptions are in appendix B.

    (man 3 also)
*/
#include <stdio.h>
#include <stdlib.h>

void strncat(char *s, char *t, int n) {
  while(*s != 0) s++;
  // we are now at the end of 's'
  while(*t != 0 && n-- > 0) {
    *s++ = *t++;
  }
  *s = 0;
}

int main(int argc, char *argv[]) {
  strncat(argv[1], argv[2], atoi(argv[3]));
  printf("%s\n", argv[1]);
  return 0;
}