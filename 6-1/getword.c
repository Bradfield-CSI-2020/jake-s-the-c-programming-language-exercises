/*  Exercise 6-1
    Our version of getword does not properly handle underscores, string constants,
    comments, or preprocessor control lines. Write a better version.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 1000

struct key {
  char *word;
  int count;
};

struct key keytab[] = {
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  "do", 0,
  "double", 0,
  "else", 0,
  "enum", 0,
  "extern", 0,
  "float", 0,
  "for", 0,
  "goto", 0,
  "if", 0,
  "int", 0,
  "long", 0,
  "register", 0,
  "return", 0,
  "short", 0,
  "signed", 0,
  "sizeof", 0,
  "static", 0,
  "struct", 0,
  "switch", 0,
  "typedef", 0,
  "union", 0,
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0,
};

typedef struct key * Keyptr;

#define NKEYS sizeof keytab / sizeof(struct key)

int getword(char *, int);
Keyptr binsearch(char *, Keyptr, int);

int main(void) {
  char word[MAXWORD];
  Keyptr pkey;

  while(getword(word, MAXWORD) != EOF) {
    if(isalpha(word[0])) {
      // binary search keytab
      if((pkey = binsearch(word, keytab, NKEYS)) != NULL) {
        // if word is found, increment the count
        pkey->count++;
      } else {
        // if word is not found, it is not a keyword.
      }
    }
  }


  for(pkey = keytab; pkey - keytab < NKEYS; pkey++) {
    printf("%s: %d\n", pkey->word, pkey->count);
  }

  return 0;
}

Keyptr binsearch(char * target, Keyptr tab, int tablen) {
  Keyptr low = &tab[0];
  Keyptr high = &tab[tablen];
  Keyptr mid;

  int compresult = 0;

  while(high - low > 0) {
    mid = low + (high - low) / 2;
    if((compresult = strcmp(target, mid->word)) == 0) {
      return mid;
    }
    if(compresult > 0) {
      // search right
      low = mid + 1;
    } else {
      // search left
      high = mid - 1;
    }
  }
  return NULL;
}

/*
    getword fetches the next "word" from the input, where a "word" is
    either a string of letters or digits beginning with a letter,
    or a single non-whitespace character.

    The return value of the function is either EOF, the first character of the word,
    or a non-whitespace character.
*/
int getword(char * word, int maxwordlen) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while(isspace(c = getch()))
    ; /* remove leading whitespace */
  if(c != EOF) {
    *w++ = c; /* set the first character of the word to c, and point to the next character */
  }
  if(!isalpha(c)) { /* Any time we're recording something like a [, or ] or (, ) */
    *w = 0; /* set the second character of the word to \0. */
    return c;
  }
  for(; --maxwordlen > 0; w++) {
    if(!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  }
  *w = 0;
  return word[0];
}

int buffer = -1;

int getch(void) {
  int result;
  if(buffer == -1) {
    return getchar();
  } else {
    result = buffer;
    buffer = -1;
    return result;
  }
}

void ungetch(int c) {
  buffer = c;
}






