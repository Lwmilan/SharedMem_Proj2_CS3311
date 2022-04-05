#include <stdio.h>

int main(int argc, char *argv[]) {
  int qNum, xNum, yNum;
  int inputNum;
  FILE *fptr;

  if ((fptr = fopen(argv[1], "r")) == NULL) {
    printf("Error Opening File!\n");
    return 1;
  }

  // For Loading qsort array
  fscanf(fptr, "%d", &qNum);
  int qArr[qNum];
  for (int i = 0; i < qNum; i++) {
    fscanf(fptr, "%d", &inputNum);
    qArr[i] = inputNum;
  }
  for (int i = 0; i < qNum; i++) {
    printf("%d, ", qArr[i]);
  }
  printf("\n");
  fclose(fptr);
  return 0;
}
