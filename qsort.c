#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArr(int loc1, int loc2, int *arr);
int randomNumGen(int low, int high);
void swap(int loc1, int loc2, int *arr);
void qsorter(int left, int right, int *arrSort);
void printArrWptrs(int loc1, int loc2, int *arr, int lP, int rP);

void swap(int loc1, int loc2, int *arr) {

  printf("Swapped %d[%d] & %d[%d]\n", loc1, arr[loc1], loc2, arr[loc2]);
  int temp = arr[loc1];
  arr[loc1] = arr[loc2];
  arr[loc2] = temp;
}

void qsorter(int left, int right, int *arrSort) {
  // int rMid = randomNumGen(left, right);

  // int sze = right - left;
  // int rMid;
  // if (sze > 0) {
  //   rMid = (sze / 2) + left;
  // }
  if ((right - left) == 0) {
    return;
  }
  int lPoint = left;
  int rPoint = right;
  int pivot = arrSort[right];
  printf("Beginning Arr Information\n lP: %d\t rP: %d\t piv: %d\n", lPoint,
         rPoint, pivot);
  printArrWptrs(left, right, arrSort, lPoint, rPoint);

  while (lPoint < rPoint) {
    while (arrSort[lPoint] <= pivot && (lPoint < rPoint)) {
      lPoint++;
    }
    // printf("lPoint: %d\n", lPoint);
    while (arrSort[rPoint] >= pivot && (lPoint < rPoint)) {
      rPoint--;
    }

    // printf("rPoint: %d\n", rPoint);

    printArrWptrs(left, right, arrSort, lPoint, rPoint);
    if (lPoint == rPoint) {
      swap(rPoint, right, arrSort);
    } else {
      swap(lPoint, rPoint, arrSort);
    }

    printArrWptrs(left, right, arrSort, lPoint, rPoint);
    // printArr(left, right, arrSort);
  }

  printf("\n\nAfter pass\n");
  printArr(left, right, arrSort);
  printf("\n\n");
  printf("lPoint: %d\trPoint: %d\n\nCalling two new qSorts\n", lPoint, rPoint);
  if ((lPoint - left) >= 1) {
    qsorter(left, lPoint, arrSort);
  }
  if ((right - (lPoint + 1)) > 0) {
    qsorter(lPoint + 1, right, arrSort);
  }

  // qsorter(left, lPoint, arrSort);
  // qsorter(rPoint + 1, right, arrSort);
}

// while (lPoint < rPoint) {
//   while (arrSort[lPoint] <= pivot) {
//     lPoint++;
//   }
//   // printf("lPoint: %d\n", lPoint);
//   while (arrSort[rPoint] >= pivot) {
//     rPoint--;
//   }

//   printf("rPoint: %d\n", rPoint);
//   swap(lPoint, rPoint, arrSort);
//   printArr(left, right, arrSort);
// }

int main(int argc, char *argv[]) {
  // int numArray[] = {9, 7, 5, 3, 1};
  int numArray[] = {4, 76, 53, 33, 24};
  printArr(0, 4, numArray);
  // swap(2, 4, numArray);
  // printArr(0, 4, numArray);

  qsorter(0, 4, numArray);
  printf("Final Sorted Array\n");
  printArr(0, 4, numArray);

  return 0;
}

void printArr(int loc1, int loc2, int *arr) {
  for (int i = loc1; i <= loc2; i++) {
    printf("[%d], ", arr[i]);
  }
  printf("\n");
}

void printArrWptrs(int loc1, int loc2, int *arr, int lP, int rP) {
  int lPprint = (lP - loc1);
  int rPprint = (rP - loc1);
  for (int i = loc1; i <= loc2; i++) {
    if (i == lPprint && i == rPprint) {
      printf("LR->[%d], ", arr[i]);
    } else if (i == lPprint) {
      printf("L->[%d], ", arr[i]);
    } else if (i == rPprint) {
      printf("R->[%d], ", arr[i]);
    } else {
      printf("[%d], ", arr[i]);
    }
  }
  printf("\n");

  // for (int i = loc1; i <= loc2; i++) {
  //   printf("[%d], ", arr[i]);
  // }
  // printf("\n");
}

int randomNumGen(int low, int high) {
  srand(time(NULL));

  int size = (high - low);
  int comparer;
  if (size > 0) {
    comparer = rand() % (size + 1);
    printf("size: %d\trand: %d\n", size, comparer);

  } else if (size == 0) {
    comparer = -1;
    printf("size is 0: %d\n", size);

  } else {
    comparer = -1;
    printf("size is less than 0: %d\n", size);
  }
  return comparer;
}
