/*
  Add access to library functions like sin, exp, and pow. See
  <math.h> in Appendex B, section 4.
*/

#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define CLEAR 'c'
#define DUPLICATE 'd'
#define SWAP 's'
#define PRINT 'p'
#define PLUS '+'
#define MINUS '-'
#define DIVIDE '/'
#define MULTIPLY '*'
#define MODULO '%'
#define NEWLINE '\n'
#define SINE 'sin'
#define COSINE 'cos'
#define TANGENT 'tan'
#define EXPONENT '^'
#define POWER 'pow'

#define MAXVAL 100

#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);
void duplicate(void);
void swap(void);
void print(void);
void clear(void);

int main(void) {
  int type;
  double op1;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
      case DUPLICATE:
        duplicate();
        break;
      case SWAP:
        swap();
        break;
      case PRINT:
        print();
        break;
      case CLEAR:
        clear();
        break;
      case NUMBER:
        push(atof(s));
        break;
      case PLUS:
        push(pop() + pop());
        break;
      case MULTIPLY:
        push(pop() * pop());
        break;
      case MINUS:
        op2 = pop();
        push(pop() - op2);
        break;
      case DIVIDE:
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else
          printf("error: zero divisor\n");
        break;
      case MODULO:
        op2 = pop();
        op1 = pop();
        if(((int)op2 == op2) && ((int)op1 == op1)) {
          push((int)op1 % (int)op2);
        } else {
          printf("error: cannot modulus operation on double\n");
        }
        break;
      case SINE:
      case COSINE:
      case TANGENT:
      case POWER:
      case EXPONENT:
        printf("error: not implemented\n");
      case NEWLINE:
        // printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }
  return 0;
}

int sp = 0;
double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
      printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

void duplicate(void) {
  push(val[sp - 1]);
}
void swap(void) {
  double temp;
  if (sp > 1) {
    temp = val[sp - 2];
    val[sp - 2] = val[sp - 1];
    val[sp - 1] = temp;
  } else
    printf("error: cannot swap when fewer than two items on stack\n");
}
void print(void) {
  if (sp > 0)
    printf("%f\n", val[sp - 1]);
  else
    printf("error: stack empty\n");
}
void clear(void) {
  sp = 0;
}

int getch(void);
void ungetch(int);

int getop(char s[]) {
  int i, c;

  while((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c;
  i = 0;
  if(c == '-') {
    s[i] = c;
    if(!isdigit(s[++i] = c = getch())) {
      ungetch(c);
      return '-';
    }
  }
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
      buf[bufp++] = c;
}