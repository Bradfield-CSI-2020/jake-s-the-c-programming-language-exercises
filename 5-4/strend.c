/*  Exercise 5-4
    Write the function strend(s,t) which returns 1 if the string t occurs
    at the end of the string s, and zero otherwise.
*/

#include <stdio.h>

int strend(char *s, char *t) {
  char *tstart = t;
  for(; *s != 0; s++)
    ;
  for(; *t != 0; t++)
    ;
  // s and t now each point to the terminator character.
  while(*s == *t && t > tstart) {
    s--;
    t--;
  }

  // If we get to a point where the value in s no longer equals the value in t
  // If the whole string matched, t will be at tstart.

  return t == tstart ? 1 : 0;
}

int main(int argc, char *argv[]) {
  printf("%d\n", strend(argv[1], argv[2]));
  return 0;
}