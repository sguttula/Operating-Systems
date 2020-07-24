/*
This program reads in 2 files one in read only form and the other in read write form.
it searches for any string lenght greater than 16 made it of either zeroes or ones and then  compresses it to a single digit number while keeping the rest fo the string intact
this is done with pipes rather than doing it sequentially 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAXSIZE 1000
#define MAXLEN 10000

int fd1,fd2;
int mypipe[2];
char ipfile[MAXSIZE];
char opfile[MAXSIZE];
int i=0,count=0,n;
char ch='\0',c;
char plus=43;
char minus=45;
char zero=48;
char one = 49;
char counter[100];
int j=0,w,l=0;
pid_t ForkPID1;
void PipeCompress();
void PipeWrite();
void Compression(int ,int );
void writefile(int ,int );


void PipeCompress()
{
	while(l==0)
	{
		if((n=read(fd1,&c,1)==0))
		{
			if(i==0)
			{
				printf("\n***** The File is Empty. Nothing can be Read or Written *****\n");
				break;
			}
			else
			{
				l=1;
				ch=c;
				PipeWrite();
				break;
			}
		}
		else
		{
			PipeWrite();
		}
		++i;
	}
	printf("\n**** File Successfully Compressed ****\n");
}
// Compression but with a pipe instead, same formula 
void PipeWrite()
{
		if((i==0)||(count<1))
		{
			if (c == 10)
			{
				w = write(mypipe[1], &c, 1);
				ch=c;
			}
			else if (c == 32)
			{
				w = write(mypipe[1], &c, 1);
				ch=c;
			}
			else if ((c == 49) || (c == 48))
			{
				count = 1;
				ch = c;
			}

		}
		else
		{
			if((c==ch)&&(c!=10)&&(c!=32)&&(l!=1))
			{
				++count;
				ch=c;
			}
			else if((count<16))
			{
				if(ch==49)
				{
					for(j=0;j<count;j++)
					{
						w=write(mypipe[1],&ch,1);
					}
					count=1;
				}
				else if(ch==48)
				{
					for(j=0;j<count;j++)
					{
						w=write(mypipe[1],&ch,1);
					}
					count=1;
				}
				if((c==49)||(c==48)&&(l!=1))
				{
					ch=c;
				}
			}
			else if((count>=16))
			{
				sprintf(counter,"%d",count);
				int countsize=strlen(counter);
				if(ch==49)
				{
					w=write(mypipe[1],&plus,1);
					w=write(mypipe[1],(void *)(counter),countsize);
					w=write(mypipe[1],&plus,1);
					count=1;

					if((c==48))
					{
						ch=c;
					}
				}
				else
				{
					w=write(mypipe[1],&minus,1);
					w=write(mypipe[1],(void *)(counter),countsize);
					w=write(mypipe[1],&minus,1);
					count=1;
					if((c==49))
					{
						ch=c;
					}
				}
			}
			if((c==10)&&(l!=1))
			{
				w=write(mypipe[1],&c,1);
				ch=c;
				count=1;
			}
			else if((c==32)&&(l!=1))
			{
				w=write(mypipe[1],&c,1);
				ch=c;
				count=1;
			}
		}
}



void FileWrite()
{
	while(read(mypipe[0],&c,1)>0)
	{
		write(fd2,&c,1);
	}


}


int main(int argc,char **argv)
{
	if (argc != 3)
	{
		printf("\nHey argument must be 3!!");
		printf(
				"\nThe correct format is ./PipeCompress <inputfilename> <outputfilename>\n");
		
	} else {
	
		strncpy(ipfile, argv[1], MAXSIZE - 1);
		strncpy(opfile, argv[2], MAXSIZE - 1);
		printf("\n InputFile\t: %s\n Output File\t: %s\n", ipfile, opfile);

		fd1 = open(ipfile, O_RDONLY);
		if (fd1 == -1) {
			printf("\nCannot open file : %s\n", ipfile);
			printf("\nExiting now\n");
		}
		fd2 = open(opfile, O_CREAT | O_TRUNC | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd2 > 0)
		{
			
			exit(0);
		}

		if (pipe(mypipe))//Check if pipe is created
		{
			printf("\n Error pipe Failed \n");
			return (0);
		}

		else {
			// first child 
			pid_t ForkPID;
			ForkPID = fork();

			switch (ForkPID) {
			case -1:
				printf("Error: Failed to fork.\n");
				break;
			case 0:
				// write from pire and so input is closed 
				close(mypipe[0]);
				PipeCompress();
				break;

			default:
			//second child
				ForkPID1 = fork();
				switch (ForkPID1) {
				case -1:
					printf("Error: Failed to fork.\n");
					break;
				case 0:
			// write from pire and so input is closed 
					close(mypipe[1]);
					FileWrite();
					break;

				default:
				// closes the pipes and waits for both children to finish
					close(mypipe[0]);
					close(mypipe[1]);
					waitpid(ForkPID, NULL, 0);
					waitpid(ForkPID1, NULL, 0);
					printf("Fork executed successfully\n");
				}

			}
		}
	}
}
