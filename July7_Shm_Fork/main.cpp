/*
            Using shared memory from the boot Interprocess communication in
   Linux
     */
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define SHM_SIZE 30
using namespace std;
extern int etext, edata, end;
int main() {
  int shmid;
  char c, *shm, *s;
  if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0660)) < 0) {
    perror("shmget fail");
    return 1;
  }
  if ((shm = (char *)shmat(shmid, 0, 0)) == (char *)-1) {
    perror("shmat : parent");
    return 2;
  }
  cout << "Addresses in parent" << endl;
  cout << "shared mem: " << hex << (long int)(shm) << " etext: " << &etext
       << " edata: " << &edata << " end: " << &end << endl
       << endl;
  s = shm;                     // s now references shared mem
  for (c = 'A'; c <= 'Z'; ++c) // put some info there
    *s++ = c;
  *s = '\0'; // terminate the sequence
  cout << "In parent before fork, memory is: " << shm << endl;
  switch (fork()) {
  case -1:
    perror("fork");
    return 3;
  default:
    wait(0); // let the child finish
    cout << "In parent after fork, memory is : " << shm << endl;
    cout << "\nParent removing shared memory" << endl;
    shmdt(shm);
    shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);
    break;
  case 0:
    cout << "In child after fork, memory is  : " << shm << endl;
    for (; *shm; ++shm) // modify shared memory
      *shm += 32;
    shmdt(shm);
    break;
  }
  return 0;
}

////K:\J\Study-Ebook\Intercommunication processing
//#include <sys/types.h>
//#include <sys/shm.h>
//#include <stdio.h>
//#include <cstdlib>

//#define MEMSIZE 1
//#define BUFSIZE 1000
//#define NULL 0
// int main()
//{
//    int shmid, i;
//    char *buffer;
//    key_t key;
//    key = ftok("/tmp/key.dat",1);
//    printf("%d", key);
//    /* Creation of the IPC */
//    if ((shmid = shmget(IPC_PRIVATE, BUFSIZE, IPC_CREAT | 0666)) == 1) // key
//    is 15
//    {
//        perror("shared_memory");
//        exit(1);
//    }
//    /* Attach to the IPC */
//    printf("First shared memory identifier before : %d\n",shmid);
//    if ((long int) (buffer = (char *)shmat(shmid, NULL, 0)) == 0)
//    {
//        perror("myshm");
//        exit(1);
//    }
//    /* Use the shared memory */
//    for (i=0; i<BUFSIZE; i++)
//        buffer[i] = 'a';
//    buffer[BUFSIZE]='\0';
//    puts(buffer);
//    printf("First shared memory identifier after: %d\n",shmid);
/* Detach to the IPC */
//    if (shmdt(buffer) == 1)
//    {
//        perror("myshm");
//        exit(1);
//    }
//    /* Destroy the IPC */
//    if (shmctl(shmid, IPC_RMID, NULL) == 1)
//    {
//        perror("myshm");
//        exit(1);
//    }
/*	exit(0);*/
//}
