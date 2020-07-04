#include <stdio.h>

// Write the function any(s1, s2) which returns the first location in the 
// string s1 where any character from the string s2 occurs, or -1 if s1
// contains no characters from s2. (The standard library function strpbrk does
// the same job but returns a pointer to the location).

int any(char s1[], char s2[]) {
  int found = -1;
  int i = 0;
  while(s1[i] != 0 && found == -1) {
    int j = 0;
    while(s2[j] != 0 && found == -1) {
      if(s1[i] == s2[j]) {
        found = i;
      }
      j++;
    }
    i++;
  }

  return found;
}

int main(int argc, char* argv[]) {
  printf("%d\n", any(argv[1], argv[2]));
  return 0;
}