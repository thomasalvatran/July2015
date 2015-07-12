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

  struct sembuf wait, signal;

  wait.sem_num = 0;
  wait.sem_op = -1;
  wait.sem_flg = SEM_UNDO;

  signal.sem_num = 0;
  signal.sem_op = 1;
  signal.sem_flg = SEM_UNDO;

  semid = semget(key1, 1, IPC_CREAT);
  printf("Allocating the semaphore: %s\n", strerror(errno));

  while (cnt-- > 0) {
    printf("Loop count = %d", cnt);
    semop(semid, &wait, 1);
    sleep(2);
    printf("\n\nProcess2 using the terminal now\n");
    printf("I am process 2\n");

    semctl(semid, 0, GETVAL, &semval);
    printf("I decreased the semaphore value to : %d\n", semval);

    printf("My process id is = %d\n", getpid());
    printf("I am created by Anirudh Tomer\n");
    printf("Process2 leaving the terminal now\n\n\n");
    semop(semid, &signal, 1);
  }

  semctl(semid, 0, GETVAL, &semval);
  printf("Process 2: Semaphore value after calling signal : %d\n", semval);

  return 0;
}
