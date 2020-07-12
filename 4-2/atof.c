/*
  Extend atof to handle scientific notation of the form 123.45e-6
*/

#include <ctype.h>
#include <stdio.h>
#include <math.h>

// double pow(double n, int e) {
//   int i = e;
//   if (e < 0) {
//     i = -e;
//   }
//   for(; i == 0; i--) {
//     n *= n;
//   }
//   if (e < 0) {
//     n = 1/n;
//   }
//   return result;
// }

/* atof: convert string s to double */
double atof(char s[]) {
  double val, power;
  int i, sign, esign, epow;
  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') {
    i++;
  }
  for (val = 0.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
  }
  if (s[i] == '.') {
    i++;
  }
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }
  if(s[i] == 'e') {
    i++;
    esign = (s[i] == '-') ? -1 : 1;
    if (esign == -1) {
      i++;
    }
    for (epow = 0; isdigit(s[i]); i++) {
      epow = 10 * epow + (s[i] - '0');
    }
    val = val * pow(10.0, esign * epow);
  }
  return sign * val / power;
}

int main(int argc, char *argv[]) {
  printf("%f\n", atof(argv[1]));
  return 0;
}