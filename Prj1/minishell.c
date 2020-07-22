/***
This program creates your own mini unix shell letting the user put in argument less commands
such as ls or date 


***/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
char inp[25];
char *cmd[5];
int parseLine(char *);



static void prompt()
{
	printf("\nminiShell > ");
	fgets(inp,25,stdin);
	inp[strlen(inp)-1]='\0';
	parseLine(inp);
}

//parses the commands and compares if there is any | or space 
int parseLine(char * line) {
char * p;
int count = 0;
p = strtok(line, " ");
while (p && strcmp(p,"|") != 0) {
cmd[count] = p;
count++;
p = strtok(NULL," ");
}
}


int main(int argc,char **argv)
{
	prompt();

	pid_t ForkPID;
//if they type exit then they exit 
	while(strcmp(inp,"exit")!=0)
	{
		ForkPID = fork();
	switch (ForkPID) {
	case -1: printf("Error: Failed to fork.\n"); break;
	case 0:
//it forks a child process everytime a command is given 
		if (execlp(cmd[0],cmd[0], NULL) == -1) {
		printf("Error: running command: '%s'\n",cmd[0]);
		exit(0);
		}
	break;

	default:
		waitpid(ForkPID,NULL,0);
		prompt();
	}
	}


}


