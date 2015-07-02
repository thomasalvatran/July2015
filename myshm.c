//K:\J\Study-Ebook\Intercommunication processing
#include <sys/types.h>
#include <sys/shm.h>

#define MEMSIZE 1
#define BUFSIZE 1000
#define NULL 0
int main()
{
	int shmid, i;
	char *buffer;
	/* Creation of the IPC */
	if ((shmid = shmget(20, MEMSIZE, IPC_CREAT | 0666)) == 1)
	{
		perror("shared_memory");
		exit(1);
	}
	/* Attach to the IPC */
	printf("First shared memory identifier before : %d\n",shmid);
	if ((int) (buffer = shmat(shmid, NULL, 0)) == 1)
	{
		perror("myshm");
		exit(1);
	}
	/* Use the shared memory */
	for (i=0; i<BUFSIZE; i++)
		buffer[i] = 'a';
	buffer[BUFSIZE]='\0';
	puts(buffer);
	printf("First shared memory identifier after: %d\n",shmid);
	/* Detach to the IPC */
	if (shmdt(buffer) == 1)
	{
		perror("myshm");
		exit(1);
	}
	/* Destroy the IPC */
	if (shmctl(shmid, IPC_RMID, NULL) == 1)
	{
		perror("myshm");
		exit(1);
	}
/*	exit(0);*/
}

