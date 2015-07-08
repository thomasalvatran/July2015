
/*
             The PRODUCER ...
     */
     #include "local.h"
     int
     main(int argc, char *argv[]) {
       static char    *source[ROWS][COLS] = {
                      {"A", "The", "One"},
                      {" red", " polka-dot", " yellow"},
                     {" spider", " dump truck", " tree"},
                      {" broke", " ran", " fell"},
                      {" down", " away", " out"}
       };
       static char     local_buffer[SLOT_LEN];
       int             i, r, c, sleep_limit, semid, shmid;
       pid_t           ppid = getppid( );
       char            *shmptr;
       struct MEMORY   *memptr;
                                            // Check command line
      if ( argc != 2 ) {
         cerr << argv[0] << " sleep_time" << endl;
         return 20;
       }
                                            // Access, attach & ref mem
       if ((shmid=shmget((int) ppid, 0, 0)) != -1 ){
         if ((shmptr=(char *)shmat(shmid,(char *)0,0))==(char *)-1){
            perror("shmat -- producer -- attach ");
            return 21;
         }
        memptr = (struct MEMORY *) shmptr;
       } else {
         perror("shmget -- producer -- access ");
         return 22;
       }
                                            // Access semaphore set
       if ( (semid=semget((int) ppid, 2, 0)) == -1 ) {
         perror("semget -- producer -- access ");
         return 23;
       }
      sleep_limit = atoi(argv[1]) % 20;
       i = 20 - sleep_limit;
       srand((unsigned)getpid());
       while( i-- ) {
         memset(local_buffer, '\0', sizeof(local_buffer));
         for (r = 0; r < ROWS; ++r) {       // Make a random string
           c = rand() % COLS;
           strcat(local_buffer, source[r][c]);
         }
         acquire.sem_num = AVAIL_SLOTS;
        if (semop(semid, &acquire, 1 ) == -1 ){
           perror("semop -- producer -- acquire ");
           return 24;
         }
         strcpy(memptr->buffer[memptr->tail], local_buffer);
         cout << "P: [" << memptr->tail << "] "
              << memptr->buffer[memptr->tail] << endl;
         memptr->tail = (memptr->tail +1) % N_SLOTS;
         release.sem_num = TO_CONSUME;
         if (semop( semid, &release, 1 ) == -1 ) {
          perror("semop -- producer -- release ");
           return 25;
         }
         sleep( rand( ) % sleep_limit + 1 );
       }
       return 0;
     }
