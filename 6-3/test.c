#include <stdio.h>
#include <stdlib.h>

struct linkedList {
  int value;
  struct linkedList * next;
};

struct linkedList * addElement(struct linkedList *, int);

int main(void) {
  struct linkedList * head = (struct linkedList *) malloc(sizeof(struct linkedList));
  head->next = NULL;
  head = addElement(head, 1);
  head = addElement(head, 2);
  head = addElement(head, 3);
  head = addElement(head, 4);

  struct linkedList * readptr = head;
  while(readptr != NULL) {
    printf("%d\n", readptr->value);
    readptr = readptr->next;
  }
  return 0;
}

struct linkedList * addElement(struct linkedList * target, int value) {
  if(target->value == value) return target;

  struct linkedList * newNode = (struct linkedList *) malloc(sizeof(struct linkedList));
  if (newNode == NULL) return NULL;

  newNode->value = value;
  newNode->next = target;

  return newNode;
}