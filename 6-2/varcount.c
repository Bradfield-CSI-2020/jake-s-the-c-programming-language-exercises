#include <stdio.h>
/*  Exercise 6-2
    Write a C program that reads a C program and prints in alphabetical order each group
    of variable names that are identical in the first N characters, but different somewhere
    thereafter. Don't count words within strings and comments. Make N a parameter that can
    be set from the command line.
*/



// okay... so let's write a recursive descent parser for C
  // since it's just variable names that we're dealing with, maybe we just need to identify
  // variable declarations?
// How are variables declared?
  // type variablename = thing, variablename2, variablename3;
  // type variablename(type variablename, type variablename) {}
  // type can be char, int, short, double, long. Zero or more whitespace. Zero or more *. Zero or more whitespace after that.
  // variable name. Zero or more whitespace. Zero or more Assignments.

// formal grammar:
  // <declaration>:       <type> <variable>
  // <variable>:          <variablename>, <variable>
  //                      <variablename> <assignment>, <variable>
  //                      <variablename>;
  //                      <variablename> <assignment>;
  // <variablename>:          [a-Z]([a-Z0-9]?+)
  // <type>:              <typename> <whitespace>
  //                      <typename> <maybepointer>
  // <maybepointer>:      <pointer>
  //                      <pointer> <whitespace>
  //                      <whitespace> <pointer>
  //                      <whitespace> <pointer> <whitespace>
  // <whitespace>:        <whitespace-symbol>
  //                      <whitespace> <whitespace-symbol>
  // <whitespace-symbol>: [newline, space, carriage return, tab, etc.]
  // <pointer>:           *
  //                      <pointer> *
  // <typename>:          builtin
  //                      <modifier> <whitespace> builtin
  // <modifier>:          <modifiername>
  //                      <modifier> <whitespace> <modifiername>
  // <modifiername>:      [unsigned, extern, auto, register, static, etc.]
  // builtin:             int
  //                      double
  //                      char
  //                      float
  //                      long
  //                      short
  // <assignment>:        <whitespace> = stuff

// And then as we hit a variable name, we need to record it.

int main(void) {
  int bob;
  int*bob2=&bob;
  *bob2 = 1;
  printf("%d\n", *bob2);
}