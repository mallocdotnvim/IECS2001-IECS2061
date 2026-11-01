#include <stdio.h>
#include <stdlib.h>
#define ROW 4
#define COL 4

typedef struct sparse_matrix {
  int row;
  int col;
  int value;
} sparse;

int matr[ROW][COL] = {
  1, 0, 0, 0,
  0, 2, 0, 0,
  0, 0, 3, 0,
  0, 0, 4, 0 
};

int main(void)
{
  sparse sp[5]; int sp_index = 1;
  sp[0] = (sparse){.row = ROW, .col = COL, .value = 4};
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      if (matr[i][j] != 0) {
        sp[sp_index++] = (sparse){.row = i, .col = j, .value = matr[i][j]};
      }
    }
  }

  printf("original: \n");
  for (int i = 0; i < 5; i++) {
    printf("%d %d %d\n", sp[i].row, sp[i].col, sp[i].value);
  }

  int rowterms[COL] = {0},
      startpos[COL] = {0};
  for (int i = 1; i <= sp[0].value; i++) {
    rowterms[sp[i].col]++;
  }
  
  startpos[0] = 1;
  
  for (int i = 1; i < COL; i++) {
    startpos[i] = startpos[i - 1] + rowterms[i - 1];
  }
  sparse transpose[5];
  transpose[0] = (sparse){COL, ROW, sp[0].value};
  for (int i = 1; i <= sp[0].value; i++) {
    int j = startpos[sp[i].col]++;
    transpose[j] = (sparse){.row = sp[i].col, .col = sp[i].row, .value = sp[i].value};
  }

  printf("transpose: \n");
  for (int i = 0; i < 5; i++) {
    printf("%d %d %d\n", transpose[i].row, transpose[i].col, transpose[i].value);
  }
  return 0;
}