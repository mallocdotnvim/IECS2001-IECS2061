#include <stdio.h>
#include <stdlib.h>

void rec(char bit[], int i, int n) {
  if (i == n) {
    printf("%s\n", bit);
    return;
  }

  bit[i] = '0';
  rec(bit, i + 1, n);
  bit[i] = '1';
  rec(bit, i + 1, n);
}

int main(void) 
{
  printf("Input a number: ");
  int x; scanf("%d", &x);
  printf("\n");

  char *bit = malloc(sizeof(char) * (1 << x));
  
  rec(bit, 0, x);

  return 0;
}