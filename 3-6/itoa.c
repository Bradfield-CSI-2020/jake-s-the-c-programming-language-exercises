/*
  Write a version of itoa that accepts three arguments instead of two.
  The third argument is a minimum field width; the converted number must
  be padded with blanks on the left if necessary to make it wide enough.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(char s[]) {
  int len = strlen(s);
  for(int i = 0; i < len/2; i++) {
    char temp = s[i];
    s[i] = s[len-1-i];
    s[len-1-i] = temp;
  }
}

/* itoa: convert n to characters in s */
void itoa2(int n, char s[], int width) {
  int i = 0, sign;
  long ncopy = (long)n;

  sign = n > 0 ? 1 : -1;
  if (sign < 0)
    ncopy *= sign;
  do {
    s[i++] = (int)(ncopy % (long)10) + '0';
  } while ((ncopy /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  for(; i < width; i++) {
    s[i] = ' ';
  }
  reverse(s);
  s[i] = '\0';
}

int main(int argc, char *argv[]) {
  char result[200] = "";
  itoa2(atoi(argv[1]), result, atoi(argv[2]));
  printf("%s\n", result);
  return 0;
}