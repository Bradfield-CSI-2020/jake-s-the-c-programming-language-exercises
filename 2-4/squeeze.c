#include <stdio.h>
#include <string.h>
// write an alternate version of squeeze
// that removes all characters in s1
// that are present in s2.

void squeeze(char s1[], char s2[]) {
  int lenstr1 = strlen(s1);
  int lenstr2 = strlen(s2);
  int k = 0;
  int found;
  for(int i = 0; i < lenstr1; i++) {
    found = 0;
    for(int j = 0; j < lenstr2; j++) {
      if(s1[i] == s2[j]) {
        found = 1;
      }
    }
    if(found == 0) {
      s1[k] = s1[i];
      k++;
    }
  }
  s1[k] = 0;
}

int main(int argc, char* argv[]) {
  char *s1 = strdup(argv[1]);
  char *s2 = strdup(argv[2]);
  squeeze(s1, s2);
  printf("%s\n", s1);
  return 0;
}