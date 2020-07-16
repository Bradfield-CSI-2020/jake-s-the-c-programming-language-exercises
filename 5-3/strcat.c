/*  Exercise 5-3
    Write a pointer version of the function strcat that we showed in chapter 2.
    strcat(s,t) copies the string t to the end of s.
*/

#include <stdio.h>

void strcat(char *s, char *t) {
  /* how big is 's'? How can we know what has been allocated?
  How can we know that copying 't' past the 0 character won't
  overwrite something that some other part of the program is using?
  */
  for(; *s != 0; s++)
    ;
  for(; *t != 0; t++, s++) {
    (*s) = *t;
  }
  (*s) = 0;
}

int main(int argc, char *argv[]) {
  strcat(argv[1], argv[2]);
  printf("%s\n", argv[1]);
  return 0;
}