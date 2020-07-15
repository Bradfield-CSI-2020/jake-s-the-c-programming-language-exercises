/*
  Exercise 5-2
  Write getfloat, the floating point analog of getint.
  
  > What type does getfloat return as its function value?
  An int? The return value is for determining the character code
  of the most recent character. It's meant mainly for returning
  EOF at the end so we know when to stop.
*/
#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getfloat: get next float from input into *pn */
int getfloat(double *pn) {
  int c, sign;
  double power = 1.0;

  while (isspace(c = getch())) /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);                /* it's not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
  }
  if(isdigit(c)) {
    for (*pn = 0; isdigit(c); c = getch()) {
      *pn = 10 * *pn + (c - '0');
    }
    if (c == '.')
    while (isdigit(c = getch())) {
      *pn = 10 * *pn + (c - '0');
      power *= 10.0;
    }
    *pn *= sign;
    *pn /= power;
  }
  if (c != EOF) {
    ungetch(c);
  }
  return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next free position in buf */

int getch(void) {     /* get a (possibly pushed back) character */
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}

int main(void) {
  int type;
  double *pn;

  while ((type = getfloat(pn)) != EOF) {
    printf("%f\n", *pn);
  }

  return 0;
}