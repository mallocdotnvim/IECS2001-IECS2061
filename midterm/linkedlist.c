#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int value;
  struct node *next;
} node;

node *createList(int n)
{
  node *head = NULL;
  node *curr = head;
  for (int i = 0; i < n; i++) {
    node *newnode = malloc(sizeof(node));
    newnode->value = i; newnode->next = NULL;

    if (head == NULL) {
      head = newnode;
    } else {
      curr->next = newnode;
    }
    curr = newnode;
  }
  return head;
}

int main(void)
{
  node *head = createList(10);

  for (node *curr = head; curr != NULL; curr = curr->next) {
    printf("%d\n", curr->value);
  }
  return 0;
}