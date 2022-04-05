#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
** Inputs Given by command line from main
** ./qsort.c high arr[]
*/

/*
** TODO Still
**
**
**
*/
void swap(int loc1, int loc2, int *arr);
int getPart(int low, int high, int *arr);
void sort(int low, int high, int *arr);
void printArr(int loc1, int loc2, int *arr);
void printArrWptrs(int loc1, int loc2, int *arr, int lP, int rP);
void finalCheck(int high, int *arr);
/*
//
//
*/
void sort(int low, int high, int *arr) {
  if (low < high) {
    /*
    **
    **  Most Likely Place to Implement the Threads
    **
    */
    int partition = getPart(low, high, arr);

    printf("\n\n--------Sort--------\n");
    printf("--------Low: %d\t High:%d\tPartition: %d\n\n", low, high,
           partition);
    sort(low, partition - 1, arr);
    sort(partition + 1, high, arr);
  } else {
    printf("\n\n&&&&&&&&No Sort&&&&&&&&\n");
    printf("&&&&&&&&Low: %d\t High:%d\n\n", low, high);
  }
}
/*
//
//
*/
int getPart(int low, int high, int *arr) {
  int pivPlace = high;
  int pivValue = arr[high];

  int lPointer = low;
  int rPointer = high;
  // int placeHolder = low - 1;

  printf("***************Array Begin***************\n");
  printf("\nGiven Array\n");
  printArr(low, high, arr);
  printf("\n");

  printArrWptrs(0, 9, arr, lPointer, rPointer);
  printf("\tP{ %d }\n", pivValue);
  // printf("\t|| Piv{ %d }\n", pivValue);

  while (lPointer < rPointer) {
    if (arr[lPointer] > pivValue && arr[rPointer] < pivValue) {
      swap(lPointer, rPointer, arr);
    } else {
      if (arr[lPointer] <= pivValue) {
        lPointer++;
      } else if ((arr[lPointer] > pivValue) && (arr[rPointer] >= pivValue) &&
                 lPointer < rPointer) {
        rPointer--;
      }
    }
    printArrWptrs(0, 9, arr, lPointer, rPointer);
    printf("\tP{ %d }\n", pivValue);
  }

  if (rPointer != pivPlace) {
    swap(rPointer, pivPlace, arr);
  }
  printf("\nFinal Array Values\nLP: %d\tRP: %d\tPivot: %d\nLow: %d\tHigh: %d\n",
         lPointer, rPointer, pivValue, low, high);

  printArr(0, 9, arr);
  printf("***************End***************\n\n\n\n");

  return rPointer;
}
/*
//
//
*/
void swap(int loc1, int loc2, int *arr) {
  /*
  ***Only Place Data Manipulation Happends. May need to create a Lock
  */
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
  int numArray[] = {667, 517, 520, 416, 362, 707, 779, 89, 280, 395};
  // printArr(0, 9, numArray);
  sort(0, 9, numArray);
  printf("Final Sorted Array\n");
  printArr(0, 9, numArray);
  finalCheck(9, numArray);
  return 0;
}
/*
//
//
*/
void printArr(int loc1, int loc2, int *arr) {
  for (int i = loc1; i <= loc2; i++) {
    if (i != loc2) {
      printf("[%d], ", arr[i]);
    } else {
      printf("[%d]\n", arr[i]);
    }
  }
}

void printArrWptrs(int loc1, int loc2, int *arr, int lP, int rP) {
  int lPprint = (lP - loc1);
  int rPprint = (rP - loc1);
  for (int i = loc1; i <= loc2; i++) {
    if (i == loc2) {
      if (i == lPprint && i == rPprint) {
        printf("LR->[%d]", arr[i]);
      } else if (i == lPprint) {
        printf("L->[%d]", arr[i]);
      } else if (i == rPprint) {
        printf("R->[%d]", arr[i]);
      } else {
        printf("[%d]", arr[i]);
      }
    } else {
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
  }
}
void finalCheck(int high, int *arr) {
  int toggleCheck = 0;
  for (int i = 0; i < high; i++) {
    if (arr[i] > arr[i + 1]) {
      toggleCheck++;
      printf("\n\n\nERROR %d[ %d ] > %d[ %d ]\n\n\n", i, arr[i], i + 1,
             arr[i + 1]);
    }
  }
  if (toggleCheck == 0) {
    printf("Final Array Check Passed\n");
  }
}
// for (int i = loc1; i <= loc2; i++) {
//   printf("[%d], ", arr[i]);
// }
// printf("\n");
