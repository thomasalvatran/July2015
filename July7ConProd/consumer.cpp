/*
        The CONSUMER
 */
#include "local.h"
int
main(int argc, char *argv[]) {
  static char    local_buffer[SLOT_LEN];
  int            i, sleep_limit, semid, shmid;
  pid_t          ppid = getppid( );
 char           *shmptr;
  struct MEMORY  *memptr;
                                       // Check command line
  if ( argc != 2 ) {
    cerr << argv[0] << " sleep_time" << endl;
    return 30;
  }
                                       // Access, attach & ref memory
  if ((shmid=shmget((int) ppid, 0, 0)) != -1 ){
    if ( (shmptr=(char *)shmat(shmid,(char *)0,0)) == (char *) -1){
     perror("shmat -- consumer -- attach");
      return 31;
    }
    memptr = (struct MEMORY *) shmptr;
  } else {
    perror("shmget -- consumer -- access");
    return 32;
  }
                                       // Access semaphore set
  if ( (semid=semget((int) ppid, 2, 0)) == -1 ) {
   perror("semget -- consumer -- access ");
    return 33;
  }
  sleep_limit = atoi(argv[1]) % 20;
  i = 20 - sleep_limit;
  srand((unsigned)getpid());
  while( i ) {
    acquire.sem_num = TO_CONSUME;
    if (semop(semid, &acquire, 1 ) == -1 ){
      perror("semop -- consumer -- acquire ");
     return 34;
    }
    memset(local_buffer, '\0', sizeof(local_buffer));
    strcpy(local_buffer, memptr->buffer[memptr->head]);
    cout << "C: [" << memptr->head << "] "
         << local_buffer << endl;
    memptr->head = (memptr->head +1) % N_SLOTS;
    release.sem_num = AVAIL_SLOTS;
    if (semop( semid, &release, 1 ) == -1 ) {
      perror("semop -- consumer -- release ");
     return 35;
    }
    sleep( rand( ) % sleep_limit + 1 );
  }
  return 0;
}
