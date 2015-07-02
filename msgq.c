/*http://people.cs.aau.dk/~adavid/teaching/MTP-05/lectures/13/Inter-Process_Communication.pdf*/
//K:\J\Study-Ebook\Intercommunication processing
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mymsg {
	long mtype;
	char *mtext;
};
int main() {
	int msqid;
	struct mymsg msg;
	char buffer[10] = "abcdefghi\0";
	msg.mtype = 1;
	msg.mtext = buffer;
	/* Creation of the IPC */
	if ((msqid = msgget(20, 0666 | IPC_CREAT)) == 1)
	{
		perror("mymsg");
		exit(1);
	}
	/* Sending a message */
	msgsnd(msqid, &msg, 3, 0);
	sleep(1);
	/* Receiving a message */
	msgrcv(msqid, &msg, 3, 1, 0);
	printf("The message is: %s\n", msg.mtext);
	exit(0);
}

