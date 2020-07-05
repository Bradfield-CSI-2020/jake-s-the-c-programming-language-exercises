#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// write a function setbits(x,p,n,y) that returns x with the n bits that begin
// at position p set to the rightmost n bits of y, leaving the other bits unchanged.

// e.g.
// x = 1111
// y = 0101
// p = 1
// n = 2
// setbits(x,p,n,y) => 1011


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

int setbits(int x, int y, int p, int n) {
  return (x & ~((~(~0 << n)) << p)) | ((y & ~(~0 << n)) << p);

}


int main(int argc, char *argv[]) {
  print_binary(setbits(atob(argv[1]), atob(argv[2]), atoi(argv[3]), atoi(argv[4])));
  return 0;
}