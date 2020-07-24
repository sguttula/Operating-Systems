/*
This program reads in 2 files one in read only form and the other in read write form.
it searches for any string with a digit accompanied by either + or -  decompresses it to a long string of either zeros or ones  while keeping the rest of the string intact

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
char ipfile[MAXSIZE];
char opfile[MAXSIZE];


char ch = '\0', c;
char plus = 43;
char minus = 45;
char counter[100];
char zero=48;
char one = 49;


int i, j, k, w, n = 1, count = 1, v = 0,l=0;
void Decompression(int ,int );
void writefile(int ,int );


int main(int argc, char **argv) {
	int filedes1, filedes2;
	if (argc != 3)//checking for number of arguments
	{
		printf("\nHey argument must be 3!!");
		printf(
				"\nThe correct format is ./MyDecompress <inputfilename> <outputfilename>\n");
	}
	else
	{
		printf("\ncorrect number of Arguments\n");
		strncpy(ipfile, argv[1], MAXSIZE - 1);//Storing the input and output file name from arguments
		strncpy(opfile, argv[2], MAXSIZE - 1);
		printf("\n Input File\t: %s\n Output File\t: %s\n", ipfile, opfile);

		filedes1 = open(ipfile, O_RDONLY);

		if (filedes1 == -1)
		{
			printf("\nCannot open file : %s\n", ipfile);
			printf("\nExiting now\n");
			exit(0);
		}

		filedes2 = open(opfile, O_CREAT | O_TRUNC| O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

		if(filedes2>0)
		{
			printf("\nFile created successfully\n");
		}

		Decompression(filedes1, filedes2);
		printf("\nProgram Successfully Decompressed your file\n\n");
		close(filedes1);
		close(filedes2);
		return 0;
	}
}


void Decompression(int fd1, int fd2) {
	while(l==0)
	{
		if((n=read(fd1,&c,1))==0)
		{
			if(i==0)
			{
				printf("\n*****The File is Empty. Nothing can be written*****\n");
				break;
			}
			else
			{
				l=1;
			}
		}
		else
		{
			writefile(fd1,fd2);
		}
		++i;

	}//End of while

}
void writefile(int fd1, int fd2)
{
	//Writes to the file if the read character is 1,0,' ','\n'

	if ((c == 10))
	{
		w = write(fd2, (&c), 1);
	}
	else if ((c == 32))
	{
		w = write(fd2, &c, 1);
	}
	else if (c == one)
	{
		w = write(fd2, &c, 1);
		count = 1;
	}
	else if (c == zero)
	{
		w = write(fd2, &c, 1);
		count = 1;
	}
	// if it is + or - it parses the digit and gives you either ones or zeros 
	else if (c == plus)
	{
		memset(counter, '\0', 100);
		n=read(fd1,&c,1);
		for (i = i + 1, v = 0; (c != 43); ++i, ++v)
		{
			counter[v] = c;
			n=read(fd1,&c,1);
		}
		int counti = atoi(counter);
		for (k = 0; k < counti; k++)
		{
			w = write(fd2, &one, 1);
		}
	}
	else if (c == minus)
		{
			memset(counter, '\0', 100);
			n=read(fd1,&c,1);
			for (i = i + 1, v = 0; (c != 45); ++i, ++v)
			{
				counter[v] = c;
				n=read(fd1,&c,1);
			}
			int counti = atoi(counter);
			for (k = 0; k < counti; k++)
			{
				w = write(fd2, &zero, 1);
			}
		}
}
