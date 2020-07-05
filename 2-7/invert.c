#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// write a function invert(x,p,n) that returns x with the n bits that
// begin at position p inverted (i.e., 1 changed into 0 and vice versa),
// leaving the others unchanged.

// n = 2; p = 2
//                   ~0 -> 11111111
//              ~0 << n -> 11111100
//         (~(~0 << n)) -> 00000011
//   (~(~0 << n )) << p -> 00001100
// ~((~(~0 << n)) << p) -> 11110011

char* itoa(int val, int base){
  
  static char buf[32] = {0};
  
  int i = 30;
  
  for(; val && i ; --i, val /= base)
  
    buf[i] = "0123456789abcdef"[val % base];
  
  return &buf[i+1];
  
}

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

void print_binary(int number)
{
    printf("binary: %s\n",itoa(number,2));
}

int invert(int x, int p, int n) {
  return (~x & ((~(~0 << n)) << p)) | (x & (~((~(~0 << n )) << p )));
}

int main(int argc, char *argv[]) {
  print_binary(invert(atob(argv[1]), atoi(argv[2]), atoi(argv[3])));
  return 0;
}