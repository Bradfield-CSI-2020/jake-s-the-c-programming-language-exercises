#include <stdio.h>
// Rewrite the function lower, which converts upper case letters into lower case,
// with a conditional expression instead of if-else.

char lowercharacter(char input) {
  return input == 'A'
    ? 'a'
    : input == 'B'
      ? 'b'
      : input == 'C'
        ? 'c'
        : input == 'D'
          ? 'd'
          : input == 'E'
            ? 'e'
            : input == 'F'
              ? 'f'
              : input == 'G'
                ? 'g'
                : input == 'H'
                  ? 'h'
                  : input == 'I'
                    ? 'i'
                    : input == 'J'
                      ? 'j'
                      : input == 'K'
                        ? 'k'
                        : input == 'L'
                          ? 'l'
                          : input == 'M'
                            ? 'm'
                            : input == 'N'
                              ? 'n'
                              : input == 'O'
                                ? 'o'
                                : input == 'P'
                                  ? 'p'
                                  : input == 'Q'
                                    ? 'q'
                                    : input == 'R'
                                      ? 'r'
                                      : input == 'S'
                                        ? 's'
                                        : input == 'T'
                                          ? 't'
                                          : input == 'U'
                                            ? 'u'
                                            : input == 'V'
                                              ? 'v'
                                              : input == 'W'
                                                ? 'w'
                                                : input == 'X'
                                                  ? 'x'
                                                  : input == 'Y'
                                                    ? 'y'
                                                    : input == 'Z'
                                                      ? 'z'
                                                      : input;
}

char* lower(char input[]) {
  int i = 0;
  while (input[i] != '\0') {
    input[i] = lowercharacter(input[i]);
    i++;
  }
  return input;
}

int main(int argc, char *argv[]) {
  for(int i = 1; i < argc; i++) {
    printf("%s\n", lower(argv[i]));
  }
  return 0;
}