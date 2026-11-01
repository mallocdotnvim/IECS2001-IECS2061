#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct queue {
  int front;
  int rear;
  int count;
  int array[SIZE];
} queue;

_Bool enqueue(queue *q, int items)
{
  if (q->count == SIZE) return 0;
  q->array[q->rear] = items;
  q->rear = (q->rear + 1) % SIZE;
  q->count++;

  return 1;
}

int dequeue(queue *q)
{
  if (q->count == 0) return -1;
  int element = q->array[q->front];
  q->front = (q->front + 1) % SIZE;
  q->count--;
  return element;
}

_Bool empty(queue *q)
{
  return q->count == 0;
}

int main(void)
{
  queue q = {0, 0, 0, {0}};
  for (int i = 1; i <= 5; i++) {
    enqueue(&q, i * 10);
    printf("%d\n", dequeue(&q));
  }
  return 0;
}