#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //For wait() probably can delete later

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
// Debugging vscode see entire array
//     *(int(*)[10])xArr
//  Use shmget() to allocate a shared memory.
//  Use shmat() to attach a shared memory to an address space.
//  Use shmdt() to detach a shared memory from an address space.
//  Use shmctl() to deallocate a shared memory.
//  #include  <sys/types.h>
//  #include  <sys/ipc.h>
//  #include  <sys/shm.h>

// Use execvp() to call other programs

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
  // For Loading xsort array
  fscanf(fptr, "%d", &xNum);
  int xArr[xNum];
  for (int i = 0; i < xNum; i++) {
    fscanf(fptr, "%d", &inputNum);
    xArr[i] = inputNum;
  }
  // For Loading xsort array
  fscanf(fptr, "%d", &yNum);
  int yArr[yNum];
  for (int i = 0; i < yNum; i++) {
    fscanf(fptr, "%d", &inputNum);
    yArr[i] = inputNum;
  }
  fclose(fptr);

  printf("qNum: %d\txNum: %d\tyNum: %d\n", qNum, xNum, yNum);
  // Just For Printing the qArr
  for (int i = 0; i < qNum; i++) {
    if (i != (qNum - 1)) {
      printf("%d, ", qArr[i]);
    } else {
      printf("%d\n", qArr[i]);
    }
  }
  // Just For Printing the xArr
  for (int i = 0; i < xNum; i++) {
    if (i != (xNum - 1)) {
      printf("%d, ", xArr[i]);
    } else {
      printf("%d\n", xArr[i]);
    }
  }
  // Just For Printing the yArr
  for (int i = 0; i < yNum; i++) {
    if (i != (yNum - 1)) {
      printf("%d, ", yArr[i]);
    } else {
      printf("%d\n", yArr[i]);
    }
  }

  /*
  ******Creating QSort Shared Memory*****
  */
  int qShmID;
  key_t qKey;
  int *qShared;
  char *qCom = "./qsort";
  char qcomMax[20];
  char qcomShaID[20];
  // "q" = 113 ID to use for qsort shared memory
  // "a" = 97 ID to use for xArr shared memory
  // "z" = 122 ID to use for yArr shared memory
  qKey = ftok("./", 113);
  qShmID = shmget(qKey, sizeof(int[qNum]), IPC_CREAT | 0666);
  qShared = (int *)shmat(qShmID, NULL, 0);
  if (qShared < 0) {
    printf("shmat Failed for qShared");
    return 1;
  }
  // Loading qShared Array
  for (int i = 0; i < qNum; i++) {
    qShared[i] = qArr[i];
  }
  sprintf(qcomMax, "%d", qNum);
  sprintf(qcomShaID, "%d", qShmID);
  char *qargList[] = {qCom, qcomShaID, qcomMax, NULL};

  /*
  ******Creating xArr Shared Memory*****
  */
  int xShmID;
  key_t xKey;
  int *xShared;
  char *mCom = "./merge";
  char xcomMax[20];
  char xcomShaID[20];
  // "q" = 113 ID to use for qsort shared memory
  // "a" = 97 ID to use for xArr shared memory
  // "z" = 122 ID to use for yArr shared memory
  xKey = ftok("./", 97);
  xShmID = shmget(xKey, sizeof(int[xNum]), IPC_CREAT | 0666);
  xShared = (int *)shmat(xShmID, NULL, 0);
  if (xShared < 0) {
    printf("shmat Failed for xShared");
    return 1;
  }

  // Setting all values to 0
  for (int i = 0; i < xNum; i++) {
    xShared[i] = 0;
  }
  // Loading xShared Array
  for (int i = 0; i < xNum; i++) {
    xShared[i] = xArr[i];
  }

  sprintf(xcomMax, "%d", xNum);
  sprintf(xcomShaID, "%d", xShmID);

  /*
  ******Creating yArr Shared Memory*****
  */
  int yShmID;
  key_t yKey;
  int *yShared;
  char ycomMax[20];
  char ycomShaID[20];
  // "q" = 113 ID to use for qsort shared memory
  // "a" = 97 ID to use for xArr shared memory
  // "z" = 122 ID to use for yArr shared memory
  yKey = ftok("./", 122);
  yShmID = shmget(yKey, sizeof(int[yNum]), IPC_CREAT | 0666);
  yShared = (int *)shmat(yShmID, NULL, 0);
  if (yShared < 0) {
    printf("shmat Failed for yShared");
    return 1;
  }
  // Clearing Y Array
  for (int i = 0; i < yNum; i++) {
    yShared[i] = 0;
  }
  // Loading yShared Array
  for (int i = 0; i < yNum; i++) {
    yShared[i] = yArr[i];
  }

  sprintf(ycomMax, "%d", yNum);
  sprintf(ycomShaID, "%d", yShmID);

  /*
   ******Creating cArr Shared Memory*****
   */
  int cShmID;
  key_t cKey;
  int *cShared;
  char ccomShaID[20];
  // "q" = 113 ID to use for qsort shared memory
  // "a" = 97 ID to use for xArr shared memory
  // "z" = 122 ID to use for yArr shared memory
  // "G" = 71 ID to use for cArr shared memory
  cKey = ftok("./", 71);
  cShmID = shmget(cKey, sizeof(int[xNum + yNum]), IPC_CREAT | 0666);
  cShared = (int *)shmat(cShmID, NULL, 0);
  if (cShared < 0) {
    printf("shmat Failed for cShared");
    return 1;
  }
  // Clearing C Array
  for (int i = 0; i < (xNum + yNum); i++) {
    cShared[i] = 0;
  }

  sprintf(ccomShaID, "%d", cShmID);
  char *margList[] = {mCom,    xcomShaID, xcomMax, ycomShaID,
                      ycomMax, ccomShaID, NULL};

  // sleep(10);
  printf("LAST CONSOLE PRINT BEFORE THE KRAKEN IS RELEASED\n");

  int status;
  // Call Ready to Call merge.c
  if (fork() == 0) {
    printf("[son] pid %d from [parent] pid %d\n\tCalling merge.c\n", getpid(),
           getppid());
    sleep(15);
    execvp(margList[0], margList);
    exit(1);
  }
  if (fork() == 0) {
    printf("[son] pid %d from [parent] pid %d\n\tCalling qsort.c\n", getpid(),
           getppid());
    execvp(qargList[0], qargList);
    exit(1);
  } else {
    for (int i = 1; i <= 2; i++) {
      wait(&status);
    }
  }

  /*
  -------------------TODO-------------------
  Next up is to make an empty array for merge to put all of the numbers in their
  order Check to see if all programs are getting the correct information
  */
  /*
  ********* ONLY PRINTING SHARED ARRAYS FROM HERE
  */
  // for (int i = 0; i < 3; i++) {
  //   printf("%s\t", qargList[i]);
  // }
  // printf("\n");
  // for (int i = 0; i < 6; i++) {
  //   printf("%s\t", margList[i]);
  // }
  // printf("\n");

  // // Just For Printing the shared qArray
  // printf("qArr \n");
  // for (int i = 0; i < qNum; i++) {
  //   if (i != (qNum - 1)) {
  //     printf("%d, ", qShared[i]);
  //   } else {
  //     printf("%d\n", qShared[i]);
  //   }
  // }
  // printf("xArr \n");
  // for (int i = 0; i < xNum; i++) {
  //   if (i != (xNum - 1)) {
  //     printf("%d, ", xShared[i]);
  //   } else {
  //     printf("%d\n", xShared[i]);
  //   }
  // }

  // printf("yArr \n");
  // for (int i = 0; i < yNum; i++) {
  //   if (i != (yNum - 1)) {
  //     printf("%d, ", yShared[i]);
  //   } else {
  //     printf("%d\n", yShared[i]);
  //   }
  // }

  // char* mArgs[] = {ShmID, qNum, NULL};
  // execvp();
  return 0;
}

/*
  Used by other proccesses to access shared memory
  int *qShared;
  qShared = (int *)shmat(ShmID, NULL, 0);
*/
