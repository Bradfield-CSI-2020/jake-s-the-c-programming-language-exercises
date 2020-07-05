#include <stdio.h>
#include <stdlib.h>
// In a two's complement number system, x &= (x-1) deletes
// the rightmost 1-bit in x. Explain why. Use this observation to write
// a faster version of bitcount.

// Two's complement number system is used to represent negative numbers.
// In a two's complement number system, a leading '1' bit represents negative.
// It's the one's complement, plus one.
// e.g.
//      0 ->  000
//     ~0 ->  111 (which is -1)
// ~0 + 1 -> 1000 -> 000
//      1 ->  001
//     ~1 ->  110 (which is -2)
// ~1 + 1 ->  111 (which is -1)

// two's complement with 3 bits:
//  0: 000
//  1: 001
//  2: 010
//  3: 011
// -4: 100
// -3: 101
// -2: 110
// -1: 111

// 011 &= 010 -> 010 (rightmost 1-bit is bit at index 0)
// 010 &= 001 -> 000 (rightmost 1-bit is bit at index 1)
// 001 &= 000 -> 000 (rightmost 1-bit is bit at index 0)
// 000 &= 111 -> 000 (There is no rightmost 1-bit)
// 111 &= 110 -> 110 (rightmost 1-bit is bit at index 0)
// 110 &= 101 -> 100 (rightmost 1-bit is bit at index 1)
// 101 &= 100 -> 100 (rightmost 1-bit is bit at index 0)

// x &=(x-1) -> x &=(x + -1)
// -1 = ~0 = 1111 1111
//  111
//   001
// + 111
// -----
//  1000


int bitcount(int x) {
  int nb = 0;
  while (x != 0) {
    x &= x-1;
    nb++;
  }
  return nb;
}

int main(int argc, char *argv[]) {
  printf("%d\n", bitcount(atoi(argv[1])));
  return 0;
}
