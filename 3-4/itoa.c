/*  In a two's complement number representation, our version of itoa does not handle the largest
    negative number, that is, the value of n equal to -(2^wordsize-1). Explain why not. Modify it
    to print that value correctly, regardless of the machine on which it runs.
*/

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

int main(int argc, char *argv[]) {
  return 0;
}