#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  Write the function itob(n,s,b) that convers the integer n
  into a base b character representation in the string s.
  In particular itob(n,s,16) formats n as a hexadecimal integer in s.
*/

int atob(char str[]) {
  int len = 0;
  int num = 0;
  while(str[len] != '\0') {
    len++;
  }
  for(int i = len-1; i >= 0; i--) {
    if(str[i] == '1') {
      num += 1 * pow(2, len-1-i);
    }
  }
  return num;
}

void reverse(char s[]) {
  int len = strlen(s);
  for(int i = 0; i < len/2; i++) {
    char temp = s[i];
    s[i] = s[len-1-i];
    s[len-1-i] = temp;
  }
}

char toalpha(int n) {
  if (n > 9) {
    return n - 10 + 'A';
  }
  return n + '0';
}

void itob(int n, char s[], int b) {
  int i = 0;
  do {
    s[i] = toalpha(n % b);
    i++;
  } while ((n /= b) > 0);
  if(b == 2) {
    for(; i < 32; i++) {
      s[i] = '0';
    }
    s[i++] = 'b';
    s[i++] = '0';
  }
  if(b == 16) {
    for(; i < 8; i++) {
      s[i] = '0';
    }
    s[i++] = 'x';
    s[i++] = '0';
  }
  reverse(s);
  s[i] = 0;
}

int main(int argc, char *argv[]) {
  char result[200] = "";
  itob(atoi(argv[1]),result, atoi(argv[2]));
  printf("%s\n", result);
  return 0;
}