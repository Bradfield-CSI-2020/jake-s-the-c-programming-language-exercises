#include <stdio.h>
#include <string.h>
/*
  Write the function strrindex(s,t) which returns the position
  of the rightmost occurrence of t in s, or -1 if there is none.
*/

int strrindex(char s[], char t) {
  int len = strlen(s);
  for(int i = len-1; i >= 0; i--) {
    if(s[i] == t) return i;
  }
  return -1;
}

int main(int argc, char *argv[]) {
  printf("%d\n", strrindex(argv[1], argv[2][0]));
  return 0;
}