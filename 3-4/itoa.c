#include <stdio.h>
#include <string.h>
#include <math.h>
/*  In a two's complement number representation, our version of itoa does not handle the largest
    negative number, that is, the value of n equal to -(2^wordsize-1). Explain why not. Modify it
    to print that value correctly, regardless of the machine on which it runs.
*/
void reverse(char s[]) {
  int len = strlen(s);
  for(int i = 0; i < len/2; i++) {
    char temp = s[i];
    s[i] = s[len-1-i];
    s[len-1-i] = temp;
  }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]) {
  int i, sign;

  if ((sign = n) < 0)       /* record sign */
    n = -n;                 /* make n positive */
  i = 0;
  do {                      /* generate digits in reverse order */
    s[i++] = n % 10 + '0';  /* get next digit */
  } while ((n /= 10) > 0);  /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

// -2147483648
// 0b1000 0000 0000 0000 0000 0000 0000 0000

/* itoa: convert n to characters in s */
void itoa2(int n, char s[]) {
  int i = 0, sign;
  long ncopy = (long)n;

  sign = n > 0 ? 1 : -1;
  if (sign < 0)
    ncopy *= sign;
  /*
    In a two's complement system, we can represent a negative value one "higher" (lower, technically) than we can represent
    a positive value. For example, with 32 bits, the maximum negative number is -2147483648 and the maximum positive
    is 2147483647. This is because 0 is represented without a leading 1 bit, and all the negative numbers are represented
    with a leading 1 bit.

    Therefore, when we say `n = -n;` in the original `itoa`, we cannot actually represent that number with 32 bits if
    it is the minimum value for a signed integer.
  */
  do {                      /* generate digits in reverse order */
    s[i++] = (int)(ncopy % (long)10) + '0';  /* get next digit */
  } while ((ncopy /= 10) > 0);  /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

int main(int argc, char *argv[]) {
  char result[200] = "";
  itoa2(-2147483648, result);
  printf("%s\n", result);
  return 0;
}