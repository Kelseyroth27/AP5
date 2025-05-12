//This is sharedTask.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFF sizeof(int)
#define KEY 34782

int main() {
    pid_t pid = fork();

    switch (pid) {
        case -1:
            // Error occurred
                         perror("fork failed");
                                     exit(EXIT_FAILURE);

 case 0: {
 // Child process
 sleep(1); // ensure parent creates shared memory first
 int shmid = shmget(KEY, BUFF, 0666);
 if (shmid < 0) {
 perror("shmget failed");                                                     
 exit(EXIT_FAILURE);                                                               }
          
                                                                                 int *data = (int *) shmat(shmid, NULL, 0);
 if (data == (int *) -1) {
 perror("shmat failed in child");
 exit(EXIT_FAILURE);
   }

 *data = 42;
 printf("Child: wrote %d to shared memory\n", *data);
 printf("Child: verifying shared memory value = %d\n", *data);

 shmdt(data);
 break;
   }


