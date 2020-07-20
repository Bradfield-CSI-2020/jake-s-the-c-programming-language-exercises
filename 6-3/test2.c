#include <stdio.h>
#include <string.h>


int main(void) {
  printf("%d\n", strcmp("aardvark", "Abacus"));
  printf("%d\n", strcmp("Abacus", "zebra"));
}