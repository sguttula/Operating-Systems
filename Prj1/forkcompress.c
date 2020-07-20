
/*
This program creates a new process to compress a file using the Mycompress.c.
The source and destination file names are to presented as command lime arguments and should be passed to execl as system call arguments
the main process waits for completion of compress operating using wait system call

*/

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc,char **argv)
{

	pid_t PID;
	PID = fork();

	switch (PID) {
	case -1: printf("Failed to fork.\n"); break;
	case 0:
		//In Child using execlp it calls MyCompress
		execlp("./mycompress", "./mycompress", argv[1],argv[2], NULL);
	break;

	default:
		//Parent process is executed here. It waits for the child to complete before exiting
		waitpid(PID,NULL,0);
		printf("Fork executed successfully\n");
	}

}

/*
Comment :
 This comes straight from the slides week 2_1

*/
