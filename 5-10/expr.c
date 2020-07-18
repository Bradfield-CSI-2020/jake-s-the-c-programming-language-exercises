/*  Exercise 5-10
    Write the program expr, which evaluates a reverse Polish expression from the command line,
    where each operator or operand is a separate argument. For example,

    expr 2 3 4 + *

    evaluates 2 x (3 + 4)
*/
#include <stdio.h>
#include <stdlib.h>

// reverse polish notation
// push 2 to the stack
// push 3 to the stack
// push 4 to the stack
// read +
// pop 4 from the stack
// pop 3 from the stack
// add them, push 7 to the stack
// read *
// pop 7 from the stack
// pop 2 from the stack
// multiply them, push 14 to the stack

int main(int argc, char * argv[]) {
  int stack[argc];
  int *stackp = stack;

  for(int i = 0; i < argc; i++) {
    stack[i] = 0;
  }

  for(int i = 1; i < argc; i++) {
    if(argv[i][0] == '+') {
      stackp--;
      *(stackp-1) = *(stackp - 1) + *stackp;
    } else if (argv[i][0] == '*') {
      stackp--;
      *(stackp-1) = *(stackp - 1) * *stackp;
    } else if (argv[i][0] == '/') {
      stackp--;
      *(stackp-1) = *(stackp - 1) / *stackp;
    } else if (argv[i][0] == '-') {
      stackp--;
      *(stackp-1) = *(stackp - 1) - *stackp;
    } else {
      *stackp = atoi(argv[i]);
      stackp++;
    }
  }

  printf("%d\n", *(stackp - 1));

  return 0;
}