//http://www.bogotobogo.com/cplusplus/multithreading_ipc.php
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t myMutex;

int main()
{
        int status, myPipe[2];
        pipe(myPipe);  // create the pipe
        pid_t pid = fork();
				printf("Main pid %d\n", getpid());
        /* child process */
        if(pid == 0)
        {
        			  printf("Fork/Child pid %d\n", getpid());
                close(myPipe[0]);  // close unused read end
                write(myPipe[1], "a", 1);
                printf("Child process sent 'a'\n");
                close(myPipe[1]);
        }

        /* parent process */
        else
        {
                char buffer[21];
                printf("Parent pid %d\n", getpid());
                close(myPipe[1]);  // close unused write end
                int pid_child = wait(&status);
                int length = read(myPipe[0], buffer, 20);
                buffer[length] = '\0';
                printf("Parent process received '%s'\n", buffer);
                close(myPipe[0]);
        }

        return 0;
}
