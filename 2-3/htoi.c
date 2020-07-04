#include <stdio.h>
#include <string.h>
#include <math.h>

// the allowable digits (including an optional 0x or 0X) are 0 through 9, a through f, and A through F.
int isvalid(char c) {
  if ((c >= 48 && c <= 57) || (c >= 65 && c <= 70) || (c >= 97 && c <= 102)) return 1;
  return 0;
}

int hexchartoint(char c) {
  if(c == '0') return 0;
  if(c == '1') return 1;
  if(c == '2') return 2;
  if(c == '3') return 3;
  if(c == '4') return 4;
  if(c == '5') return 5;
  if(c == '6') return 6;
  if(c == '7') return 7;
  if(c == '8') return 8;
  if(c == '9') return 9;
  if(c == 'a' || c == 'A') return 10;
  if(c == 'b' || c == 'B') return 11;
  if(c == 'c' || c == 'C') return 12;
  if(c == 'd' || c == 'D') return 13;
  if(c == 'e' || c == 'E') return 14;
  if(c == 'f' || c == 'F') return 15;
  return -1;
}

// convert a string of hexadecimal digits to the equivalent integer value.
int htoi(char s[]) {
  int end = 0;
  int num = 0;
  int i = strlen(s)-1;
  int count = 0;
  if(s[0] == '0') {
    if(s[1] == 'x' || s[1] == 'X') {
      end = 2;
    }
  }

  while(i >= end) {
    if(isvalid(s[i])) {
      num += hexchartoint(s[i]) * pow(16, count);
    } else {
      printf("Not valid character at %d: %c", i, s[i]);
      return -1;
    }
    count++;
    i--;
  }
  return num;
}

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    printf("%d\n", htoi(argv[i]));
  }
  return 0;
}