/*
This programs does the same compression from program one but the file now will be divided into equal chunks  (n times) and allocated it to n forks. Then assemble the result and write into a the output file
*/


#define MAXCHILD 30
#define MAXSIZE 1000
#define MAXLEN 10000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
char ipfile[MAXSIZE];
char opfile[MAXSIZE];
char charbuf[MAXLEN];
char *segment[1000];
char counter[10];
char c;
char *ch;

int i=0,j=0,s=0;
int segcount;
int n,w;
int times=0;
pid_t ForkPID;


void Compress(char *,int);


int main(int argc, char **argv) {

	
	int fd1, fd2;
	int fcount =0;
	static int l=0;

	if (argc != 3)
	{
		printf("\nThe correct format is ./ParFork <inputfilename> <outputfilename>\n");

	}
	else
	{
		
		strncpy(ipfile, argv[1], MAXSIZE - 1);
		strncpy(opfile, argv[2], MAXSIZE - 1);// storing both of the arguments  input and output files
		printf("\n InputFile\t: %s\n OutputFile\t: %s\n", ipfile, opfile);

		fd1 = open(ipfile, O_RDONLY);
		if (fd1 == -1) {
			printf("\nCannot open file : %s\n", ipfile);
			printf("\nExiting now\n");
			exit(0);
		}
		fd2 = open(opfile, O_CREAT | O_TRUNC | O_APPEND |O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd2 > 0)
		{
			printf("\n File created \n");
		}
// here were going to start to check for space or end line
//we break out of the loop and start making segments (n)
		while (l==0)
		{
			++times;
			memset(charbuf,'\0',MAXLEN);
			j=0;
			while(n = read(fd1, &c, 1) != 0)
			{
				if (c == 10||c==32)
				{
					charbuf[j] = c;
					s++;
					j = 0;
					break;
				}
				else// other wise keep writing 
				{
					charbuf[j] = c;
					j++;
				}
			}
			if(n==0)
			{
				charbuf[++j]='\0';
				l=1;
			}
			ForkPID = fork();
			fcount++;
			switch (ForkPID)
			{
			case -1:
					printf("Error: Failed to fork.\n");
					break;
			case 0:	Compress(charbuf,fd2);
					exit(0);
					break;
			default:	
				// instead of doing 3, we max it to 30 fork child processes  or the end of the file
					if (fcount >30)
					{
						while (fcount != 3){// wait untill it becomes 3 forks 
							wait(&ForkPID);
							fcount--;
						}
					}
					else if(l==1)
					{
						while (fcount!=0) 
						{
							wait(&ForkPID);
							fcount--;
						}
					}
			}
		}
	}
	printf("\nChild Process Created\t: %d\n",--times);
	
	close(fd1);
	close(fd2);
			clock_t start = clock();
			clock_t end= clock();
			printf("\nTime taken:%lf\n",(double)(end- start)*1000.0/CLOCKS_PER_SEC);


	return 0;
}

// compression of file 
void Compress(char *buf,int fd2)
{
	char plus[1],minus[1];
	plus[0]=43;
	minus[0]=45;
	char counter[100];
	int i,j,w,n=1,count=1;
	char c;
	size_t m=strlen(buf);
	for(i=0;i<=m;i++)
	{
		if(i<=0)
		{
			if (buf[i] == 10) // for  space
			{
				w = write(fd2, (void *) (&buf[i]), 1);
			}
			else if (buf[i] == 32) // for end line 
			{
				w = write(fd2, (void *) (&buf[i]), 1);
			}
		}
		else
		{
			if((buf[i]==buf[i-1])&&(buf[i]!=10)&&(buf[i]!=32))
			{
				count++;
			}
			else if((count<16))
			{
				for(j=0;j<count;j++)
				{
					w=write(fd2,(void *)(&buf[i-1]),1);
				}
				count=1;
			}
			else if(count>=16)
			{
				sprintf(counter,"%d",count);
				int countsize=strlen(counter);
				if(buf[i-1]==49)//If it is 1 and count >16
				{
					w=write(fd2,(void *)(&plus[0]),1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,(void *)(&plus[0]),1);
				}
				else//If it is 0 and count >16
				{
					w=write(fd2,(void *)(&minus[0]),1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,(void *)(&minus[0]),1);
				}
				count=1;
			}
			else if(buf[i]==10)
			{
				w=write(fd2,(void *)(&buf[i]),1);
				count=1;
			}
			else if(buf[i]==32)
			{
				w=write(fd2,(void *)(&buf[i]),1);
				count=1;
			}
		}
		continue;
	}
}
/*
Note :
how to  get the cpu speed found at stackoverflow

*/

