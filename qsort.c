#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int loc1, int loc2, int *arr);
int parter(int low, int high, int *arr);
void sort(int low, int high, int *arr);
void printArr(int loc1, int loc2, int *arr);
// void printArrWptrs(int loc1, int loc2, int *arr, int lP, int rP);
/*
//
//
*/
void sort(int low, int high, int *arr) {
  if (low < high) {
    int partition = parter(low, high, arr);
    sort(low, partition - 1, arr);
    sort(partition + 1, high, arr);
  }
}
/*
//
//
*/
int parter(int low, int high, int *arr) {
  int piv = high;
  int placeHolder = low - 1;
  for (int i = 0; i <= high - 1; i++) {
    if (arr[i] < piv) {
      placeHolder++;
      swap(placeHolder, arr[i], arr);
    }
  }
  swap(placeHolder + 1, high, arr);
  return placeHolder + 1;
}
/*
//
//
*/
void swap(int loc1, int loc2, int *arr) {
  printf("Swapped %d[%d] & %d[%d]\n", loc1, arr[loc1], loc2, arr[loc2]);
  int temp = arr[loc1];
  arr[loc1] = arr[loc2];
  arr[loc2] = temp;
}
/*
//
//
*/
int main(int argc, char *argv[]) {
  int numArray[] = {4, 76, 53, 33, 24};
  printArr(0, 4, numArray);
  sort(0, 4, numArray);
  printf("Final Sorted Array\n");
  printArr(0, 4, numArray);
  return 0;
}
/*
//
//
*/
void printArr(int loc1, int loc2, int *arr) {
  for (int i = loc1; i <= loc2; i++) {
    printf("[%d], ", arr[i]);
  }
  printf("\n");
}

// void printArrWptrs(int loc1, int loc2, int *arr, int lP, int rP) {
//   int lPprint = (lP - loc1);
//   int rPprint = (rP - loc1);
//   for (int i = loc1; i <= loc2; i++) {
//     if (i == lPprint && i == rPprint) {
//       printf("LR->[%d], ", arr[i]);
//     } else if (i == lPprint) {
//       printf("L->[%d], ", arr[i]);
//     } else if (i == rPprint) {
//       printf("R->[%d], ", arr[i]);
//     } else {
//       printf("[%d], ", arr[i]);
//     }
//   }
//   printf("\n");

//   // for (int i = loc1; i <= loc2; i++) {
//   //   printf("[%d], ", arr[i]);
//   // }
//   // printf("\n");
// }
