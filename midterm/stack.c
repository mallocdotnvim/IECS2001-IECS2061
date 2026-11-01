#include <stdio.h>
#define SIZE 200

typedef struct stack {
  int top;
  int array[SIZE];
} stack;

_Bool push(stack *st, int items) 
{
  if (st->top == SIZE - 1) {
    return 0;
  }
  st->array[++st->top] = items;
  return 1;
}

int pop(stack *st)
{
  if (st->top == -1) {
    return -1;
  }

  int element = st->array[st->top--];
  return element;
}

_Bool empty(stack *st)
{
  if (st->top == -1) {return 1;}
  return 0;
}

int main(void)
{
  stack st = {-1, {0}};
  for (int i = 0; i < 101; i++) {
    if (!push(&st, i)) {
      printf("overflow\n");
    }
  }
  printf("%d\n", empty(&st));
  for (int i = 0; i < 101; i++) {
    printf("%d\n", pop(&st));
  }
  return 0;
}