#include <stdio.h>
#include <string.h>
// Write a function escape(s, t) that converts characters like newline and tab
// into visible escape sequences like \n and \t as it copies the string t to s.
// Use a switch.
// Write a function for the other direction as well, converting escape
// sequences into real characters.

void escape(char s[], char t[]) {
  int c = strlen(t);
  for(int i = 0, j = 0; i < c; i++, j++) {
    switch(t[i]) {
      case '\n':
        s[j] = '\\';
        j++;
        s[j] = 'n';
      break;
      case '\t':
        s[j] = '\\';
        j++;
        s[j] = 't';
      break;
      default:
        s[j] = t[i];
      break;
    }
  }
}

void unescape(char s[], char t[]) {
  int c = strlen(t);
  for(int i = 0, j = 0; i < c; i++, j++) {
    if(t[i] == '\\') {
      switch(t[i+1]) {
        case 'n':
          s[j] = '\n';
          i++;
        break;
        case 't':
          s[j] = '\t';
          i++;
        break;
        default:
          s[j] = t[i];
        break;
      }
    } else {
      s[j] = t[i];
    }
  }
}

int main(int argc, char *argv[]) {
  char test[] = "Bueno\nBueno\nBueno";
  printf("Original: %s\n", test);
  char result[strlen(test)];
  escape(result, test);
  printf("%s\n", result);
  unescape(test, result);
  printf("%s\n", test);
  return 0;
}
