/***
This program creates your own mini unix shell like before but this time were using pipres and  the dup2 system call to redirect the output 

***/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

char inp[25];
char *cmd1[5];
char *cmd2[5];
int f;
int mypipe[2];
int parseline(char *,char **);

static void prompt()
{
	printf("\ndupShell > ");
	fgets(inp,25,stdin);
	inp[strlen(inp)-1]='\0';
	int count =0;
	char line1[5];

	if(strchr(inp,'|')!=NULL)

	{
	f=1;
	char *t[2];
	char *p;
	p = strtok(inp, "|");
	while (p) {
	t[count] = p;
	count++;
	p = strtok(NULL,"|");
	}
	parseline(t[0],cmd1);
	parseline(t[1],cmd2);
	}

	else
	{
		f=0;
		parseline(inp,cmd1);
	}
}


int parseline(char * line , char * cmd[]) {
char * p;
int count = 0;
p = strtok(line, " ");
while (p && strcmp(p,"|") != 0) {
cmd[count] = p;
count++;
p = strtok(NULL," ");
}
cmd[count]=NULL;
return count;
}

//forks 2 childs  and uses pipes to execute the command 

int main(int argc,char **argv)
{
	prompt();

	pid_t ForkPID,ForkPID1;

	while(strcmp(inp,"exit")!=0)
	{
		if (pipe(mypipe)) {
					printf("\npipe Failed \n");
					return (0);
				}


		ForkPID = fork();
	switch (ForkPID) {
	case -1: printf("Error: Failed to fork.\n"); break;
	case 0:

			if(f==1)
			{
			dup2(mypipe[1],STDOUT_FILENO);
//this command redirects the output of the executed command into the pipe
			close(mypipe[0]);
			close(mypipe[1]);
			}
			if (execvp(cmd1[0],cmd1) == -1) {
		printf("Error: running command: '%s'\n",cmd1[0]);
		exit(0);
		}
			exit(0);


	break;

	default:
		ForkPID1 = fork();
		switch (ForkPID1) {
			case -1: printf("Error: Failed to fork.\n"); break;
			case 0:
				dup2(mypipe[0],STDIN_FILENO); 
//this command reads from the pipe and execvp executes it
				close(mypipe[0]);
				close(mypipe[1]);
				if(f==1)
				{
				if (execvp(cmd2[0],cmd2) == -1) {
				printf("Error: running command: '%s'\n",cmd2[0]);
				exit(0);
				}
				}
				exit(0);
			break;

			default:
				close(mypipe[0]);
				close(mypipe[1]);
				waitpid(ForkPID,NULL,0);
				waitpid(ForkPID1,NULL,0);
				prompt();
			}
	}
	}


}

/*
Note
Majority of the code is the same as slides week 3_2 6-13



*/
