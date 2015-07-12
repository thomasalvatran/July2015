#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {

  key_t key1 = 12345;
  int semid;
  unsigned short semval;
  int cnt = 5;
  int childpid;

  struct sembuf wait, signal;

  wait.sem_num = 0;
  wait.sem_op = -1;
  wait.sem_flg = SEM_UNDO;

  signal.sem_num = 0;
  signal.sem_op = 1;
  signal.sem_flg = SEM_UNDO;

  semid = semget(key1, 1, IPC_CREAT);
  printf("Allocating the semaphore: %s semid %d\n", strerror(errno), semid);

  semval = 1;
  semctl(semid, 0, SETVAL, semval);
  printf("Setting semaphore value to %d: %s\n", semval, strerror(errno));

  semval = semctl(semid, 0, GETVAL);
  printf("Initialized Semaphore value to %d: %s\n", semval, strerror(errno));

  childpid = fork();

  if (childpid == 0) {
    execl("./Process2", "./Process2", NULL);
  }

  while (cnt-- > 0) {
    semop(semid, &wait, 1);
    sleep(2);
    printf("\n\nProcess1 using the terminal now\n");
    printf("I am process 1\n");

    semctl(semid, 0, GETVAL, &semval);
    printf("I decreased the semaphore value to : %d\n", semval);

    printf("My process id is = %d\n", getpid());
    printf("I am created by toshish Jawale\n");
    printf("Process1 leaving the terminal now\n\n\n");
    semop(semid, &signal, 1);
  }

  semctl(semid, 0, GETVAL, &semval);
  printf("Process 1: Semaphore value after calling signal : %d\n", semval);

  sleep(5);
  semctl(semid, 0, IPC_RMID);
  printf("Semaphore removed from the System = %s\n", strerror(errno));
  return 0;
}
