/*  Exercise 5-3
    Write a cross-referencer that prints a list of all words in a document and for each word
    prints a list of the line numbers on which it occurs. Remove noise words like "the," "and,"
    and so on.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
};

typedef struct linkedlist * LinkedListPointer;

struct treenode {
  char *word;
  struct treenode * left;   /* left nodes contain words that are "less" than the word */
  struct treenode * right;  /* right nodes contain words that are "more" than the word */
  LinkedListPointer linenumbers;
};

typedef struct treenode * TreeNodePointer;

TreeNodePointer makeTreeNode(char *, int);
LinkedListPointer insertLinkedListElement(TreeNodePointer, int);
TreeNodePointer findOrCreateTreeNode(TreeNodePointer, char *, int);
char wordisfiltered(char * word);
// char * strdup(char *);
char * lcstring(char *);

void treeprint(TreeNodePointer);

int main(void) {
  char wordbuffer[MAXWORDLEN];
  char *pword = wordbuffer;
  int c;
  int linecount = 1;
  TreeNodePointer root = NULL;

  while((c = getchar()) != EOF) {

    if(c == '\n') {
      linecount += 1;
    }
    if(isalpha(c)) {
      // add to current word and increment pointer
  
      *pword++ = c;
    } else if (pword != wordbuffer) {
  
      *pword = 0;
      pword = wordbuffer;
      pword = lcstring(pword);
      if (!wordisfiltered(wordbuffer)) {    
        root = findOrCreateTreeNode(root, pword, linecount);
      }
      // reset the pointer to the start of the word buffer.
  
      pword = wordbuffer;
    }
  }

  treeprint(root);

  // traverse our storage mechanism and print out each word and
  // the line numbers on which the word appears.
  return 0;
}

char wordisfiltered(char * word) {
  // to be implemented
  return 0;
}

TreeNodePointer makeTreeNode(char * word, int linecount) {
  TreeNodePointer t = (TreeNodePointer) malloc(sizeof(struct treenode));
  if (t == NULL) return NULL;

  t->word = strdup(word);
  t->right = NULL;
  t->left = NULL;
  t->linenumbers = NULL;
  t->linenumbers = insertLinkedListElement(t, linecount);
    
  return t;
}

// char * strdup(char * string) {
//   char * copy;

//   copy = (char *) malloc(strlen(string) + 1);  /* +1 for '\0' */
//   if (copy != NULL) {
//     strcpy(copy, string);
//   }
//   return copy;
// }

LinkedListPointer insertLinkedListElement(TreeNodePointer treenode, int lineNumber) {
  if(treenode->linenumbers != NULL && treenode->linenumbers->linenumber == lineNumber) {
    return treenode->linenumbers;
  }

  LinkedListPointer newHead = (LinkedListPointer) malloc(sizeof(struct linkedlist));
  if (newHead == NULL) return NULL;

  // if the current head is NULL, or the current head's value differs from linenUmber,
    // create new linked list element
    // set its 'next' to the address of the current head (NULL)
    // set its linenumber to lineNumbers
    // return it.

  newHead->next = treenode->linenumbers; /* Set the value of next (an address) to the value of linenumbers (an address) */
  newHead->linenumber = lineNumber;

  return newHead;
}

TreeNodePointer findOrCreateTreeNode(TreeNodePointer tnodePointer, char * word, int linecount) {
  if(tnodePointer == NULL || tnodePointer->word == NULL) {
    return makeTreeNode(word, linecount);
  }

  int comp = strcmp(tnodePointer->word, word);
  if(comp == 0) {
    tnodePointer->linenumbers = insertLinkedListElement(tnodePointer, linecount);
  } else if(comp < 0) {
    tnodePointer->right = findOrCreateTreeNode(tnodePointer->right, word, linecount);
  } else {
    tnodePointer->left = findOrCreateTreeNode(tnodePointer->left, word, linecount);
  }
  return tnodePointer;
}

void treeprint(TreeNodePointer treenode) {
  if(treenode->left != NULL) {
    treeprint(treenode->left);
  }
  LinkedListPointer temp = treenode->linenumbers;
  while(temp != NULL) {
    printf("%d ", temp->linenumber);
    temp = temp->next;
  }
  printf("%s\n", treenode->word);
  if(treenode->right != NULL) {
    treeprint(treenode->right);
  }
}

char * lcstring(char * string) {
  char * start = string;
  while(*string != 0) {
    *string = tolower(*string);
    string++;
  }
  return start;
}