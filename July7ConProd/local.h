//#ifndef LOCAL_H remove cannot have twice has been defined below otherwise error
//#define LOCAL_H
/*
        Common header file: parent, producer and consumer
     */
#ifndef LOCAL_H
#define LOCAL_H
#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>
#include <wait.h>
#define ROWS 5 // Establish some common values
#define COLS 3
#define SLOT_LEN 50
#define N_SLOTS 6
using namespace std;
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
// definition in <sys/sem.h>
#else
union semun {                // We define:
  int val;                   // value  for SETVAL
  struct semid_ds *buf;      // buffer for IPC_STAT, IPC_SET
  unsigned short int *array; // array  for GETALL, SETALL
  struct seminfo *__buf;     // buffer for IPC_INFO
};
#endif
enum { AVAIL_SLOTS, TO_CONSUME };
// Layout for shared memory
struct MEMORY {
  char buffer[N_SLOTS][SLOT_LEN];
  int head, tail;
};
// Actions for semaphores
struct sembuf acquire = {0, -1, SEM_UNDO}, release = {0, 1, SEM_UNDO};
#endif

////////////#endif // LOCAL_H  remove cannot have twice

