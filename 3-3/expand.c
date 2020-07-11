#include <ctype.h>
#include <stdio.h>
#include <string.h>
/*
  Write a function expand(s1, s2) that expands shorthand notations
  like a-z in the string s1 into the equivalent complete list abc...xyz
  in s2. Allow for letters of either case and digits, and be prepared to handle
  cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is
  taken literally.
*/

char bothAreDigits(char c1, char c2) {
  return isdigit(c1) && isdigit(c2);
}

char bothAreAlphaAndLower(char c1, char c2) {
  return isalpha(c1) && isalpha(c2) && islower(c1) && islower(c2);
}

char bothAreAlphaAndNotLower(char c1, char c2) {
  return isalpha(c1) && isalpha(c2) && !islower(c1) && !islower(c2);
}

void expand(char s1[], char s2[]) {
  // TODO: handle start > end
  // TODO: handle start == end
  int s1len = strlen(s1);
  int i, j;
  int count = 0;
  for(i = 0, j = 0; i < s1len; i++) {
    if(s1[i] == '-'
        && i > 0
        && i < s1len-1
        && (bothAreDigits(s1[i-1], s1[i+1]) || bothAreAlphaAndLower(s1[i-1], s1[i+1]) || bothAreAlphaAndNotLower(s1[i-1], s1[i+1]))) {
      j--; /* backtrack */
      for(char k = s1[i-1]; k <= s1[i+1]; k++, j++) {
        s2[j] = k;
      }
      i++; /* skip the next character */
    } else {
      s2[j] = s1[i];
      j++;
    }
  }
}

int main(int argc, char *argv[]) {
  char result[200] = "";
  expand(argv[1], result);
  printf("%s\n", result);
  return 0;
}