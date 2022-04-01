#include <stdio.h>

void findLocation(int xArr[], int yArr[], int xToFind, int ySize,
                  int fArray[]) {
  int posHolder = 0;
  while (xArr[xToFind] > yArr[posHolder]) {
    posHolder++;
  }
  printf("%d\n", posHolder);
  fArray[posHolder + xToFind] = xArr[xToFind];
}

int main() {
  int array1[] = {-20, -19, -14, -13, -11, -10, -8, -5, -3, 0,
                  4,   5,   6,   7,   8,   9,   12, 14, 16, 19};
  int array2[] = {-18, -17, -16, -15, -12, -9, -7, -6, -4, -2, -1,
                  1,   2,   3,   10,  11,  13, 15, 17, 18, 20};

  int fArr[41];

  for (int i = 0; i < 41; i++) {
    fArr[i] = -1;
  }

  // for(int i=0; i< 5; i++){

  // }
  for (int i = 0; i < 20; i++) {

    findLocation(array1, array2, i, 21, fArr);
  }
  for (int i = 0; i < 21; i++) {

    findLocation(array2, array1, i, 21, fArr);
  }

  for (int i = 0; i < 41; i++) {
    printf("%d, ", fArr[i]);
  }
}
