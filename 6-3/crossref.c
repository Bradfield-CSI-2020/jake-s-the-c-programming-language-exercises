/*  Exercise 5-3
    Write a cross-referencer that prints a list of all words in a document and for each word
    prints a list of the line numbers on which it occurs. Remove noise words like "the," "and,"
    and so on.
*/

#include <stdio.h>

#define MAXWORDLEN 100

// storage mechanism
// binary tree for individual words
// linked list for line numbers?
  // This might be easiest to implement
  // Might get inefficient for words that appear very often
  // Is there a way we can make sure the latest entry is always the head?
    // If we do that, we only have to traverse one element into the list to add.
// "dynamic" array for line numbers?
  // e.g. set array at some size N
  // when array is almost full, resize it by creating a new array at double the length
  // and then moving everything over.
  // Since we will only ever be adding things to the array, we don't really need to worry
  // about resizing in the other direction.

struct linkedlist {
  int linenumber;
  struct linkedlist * next;
}

struct treenode {
  char *word;
  struct treenode * left;   /* left nodes contain words that are "less" than the word */
  struct treenode * right;  /* right nodes contain words that are "more" than the word */
  struct linkedlist * linenumbers;
};

int main(void) {
  char wordbuffer[MAXWORDLEN];
  char *pword = wordbuffer;
  int c;
  int linecount = 1;
  while((c = getchar()) != EOF) {
    if(c == '\n') {
      linecount += 1;
    }
    if(isalpha(c)) {
      // add to current word and increment pointer
      *pword++ = c;
    } else if (pword != wordbuffer) {
      // if string in wordbuffer is not one of our filtered words,
        // if pword is not at start, we have something in the buffer.
        // try to find the word in our storage
          // if it is not present, persist the word
        // add an entry for this line number for that word
        // reset the pointer to the start of the word buffer.
    }
  }

  // traverse our storage mechanism and print out each word and
  // the line numbers on which the word appears.
  return 0;
}
