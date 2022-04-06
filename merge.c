#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
** Inputs Given by command line from main
** ./merge.c xHigh yHigh xArry[] yArr[]
*/

/*
** TODO Still
**
**
**
*/

void findLocation(int xArr[], int yArr[], int xToFind, int ySize,
                  int fArray[]) {
  int posHolder = 0;
  while (xArr[xToFind] > yArr[posHolder] && posHolder < ySize) {
    posHolder++;
  }
  printf("Given Num: %d\tLoc: %d\tposHolder: %d\tFinalPos: %d\n", xArr[xToFind],
         xToFind, posHolder, posHolder + xToFind);
  fArray[posHolder + xToFind] = xArr[xToFind];
}
/*
  Used by other proccesses to access shared memory
  int *qShared;
  qShared = (int *)shmat(ShmID, NULL, 0);
*/
int main(int argc, char *argv[]) {
  /*
  Input Args given
  ./merge xSharedID xHigh ySharedID yHigh cSharedId
  */
  int xSID = atoi(argv[1]);
  int ySID = atoi(argv[3]);
  int cSID = atoi(argv[5]);
  int xHigh = atoi(argv[2]);
  int yHigh = atoi(argv[4]);
  int cHigh = xHigh + yHigh;

  int *xArr, *yArr, *cArr;

  printf("Printed From merge\n");
  // printf("%d\n", argc);
  // for (int i = 0; i < argc; i++) {
  //   printf("%s\n", argv[i]);
  // }
  xArr = (int *)shmat(xSID, NULL, 0);
  yArr = (int *)shmat(ySID, NULL, 0);
  cArr = (int *)shmat(cSID, NULL, 0);

  printf("From Merge X Shared Array\n");
  for (int i = 0; i < xHigh; i++) {
    if (i != (xHigh - 1)) {
      printf("%d, ", xArr[i]);
    } else {
      printf("%d\n", xArr[i]);
    }
  }
  printf("From Merge Y Shared Array\n");
  for (int i = 0; i < yHigh; i++) {
    if (i != (yHigh - 1)) {
      printf("%d, ", yArr[i]);
    } else {
      printf("%d\n", yArr[i]);
    }
  }

  // for (int i = 0; i < cHigh; i++) {
  //   if (i >= xHigh) {
  //     int numLoc = i - xHigh;
  //     findLocation(yArr, xArr, numLoc, xHigh, cArr);
  //   } else {
  //     findLocation(xArr, yArr, i, yHigh, cArr);
  //   }
  // }

  pid_t pid_parent, pid_child;
  int status;
  // for (int i = 0; i < xHigh; i++) {
  //   if (fork() == 0) {
  //     printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
  //     sleep(3);
  //     findLocation(xArr, yArr, i, yHigh, cArr);
  //     sleep(3);
  //     exit(1);
  //   }
  // }
  // for (int i = 0; i < xHigh; i++) {
  //   pid_child = wait(&status);
  // }
  // After all Peramiters are calculated to call pwfind we call fork and send
  // each process off
  for (int i = 0; i < cHigh; i++) // loop will run n times (n=5)
  {
    if (fork() == 0) {

      if (i >= xHigh) {
        int numLoc = i - xHigh;
        printf("[son] pid %d from [parent] pid %d\n\ty[]: %d\t@ %d\n", getpid(),
               getppid(), yArr[numLoc], numLoc);
        sleep(2);
        findLocation(yArr, xArr, numLoc, xHigh, cArr);
      } else {
        printf("[son] pid %d from [parent] pid %d\n\tx[]: %d\t@ %d\n", getpid(),
               getppid(), xArr[i], i);
        sleep(2);
        findLocation(xArr, yArr, i, yHigh, cArr);
      }
      exit(1);
    }
  }

  // Parent Process waits for all children to Complete their calculations
  for (int i = 0; i < cHigh; i++) {
    wait(NULL);
    printf("Terminated %d of %d Processes\n", i + 1, cHigh);
  }

  printf("Final Sorted Shared Array\n");
  for (int i = 0; i < cHigh; i++) {
    if (i != (cHigh - 1)) {
      printf("%d, ", cArr[i]);
    } else {
      printf("%d\n", cArr[i]);
    }
  }

  // Detaching Shared Memory
  if (shmdt(xArr) < 0) {
    printf("Failed to detach shared memory from xArr in merge.c\n");
  }
  if (shmdt(yArr) < 0) {
    printf("Failed to detach shared memory from yArr in merge.c\n");
  }
  if (shmdt(cArr) < 0) {
    printf("Failed to detach shared memory from cArr in merge.c\n");
  }
  return 0;
  // int array1[] = {-20, -19, -14, -13, -11, -10, -8, -5, -3, 0,
  //                 4,   5,   6,   7,   8,   9,   12, 14, 16, 19};
  // int array2[] = {-18, -17, -16, -15, -12, -9, -7, -6, -4, -2, -1,
  //                 1,   2,   3,   10,  11,  13, 15, 17, 18, 20};

  // int fArr[41];

  // for (int i = 0; i < 41; i++) {
  //   fArr[i] = -1;
  // }

  // // for(int i=0; i< 5; i++){

  // // }
  // for (int i = 0; i < 20; i++) {

  //   findLocation(array1, array2, i, 21, fArr);
  // }
  // for (int i = 0; i < 21; i++) {

  //   findLocation(array2, array1, i, 21, fArr);
  // }

  // for (int i = 0; i < 41; i++) {
  //   printf("%d, ", fArr[i]);
  // }
}
