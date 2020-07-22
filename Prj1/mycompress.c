/*
This program reads in 2 files one in read only form and the other in read write form.
it searches for any string lenght greater than 16 made it of either zeroes or ones and then  compresses it to a single digit number while keeping the rest fo the string intact

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#define MAXSIZE 1000

char ipfile[MAXSIZE];
char opfile[MAXSIZE];
char ch='\0',c;
char plus=43;
char minus=45;
char zero=48;
char one = 49;
char counter[100];
int j=0,w,l=0;
int i=0,count=0,n;

void Compression(int ,int );
void writefile(int ,int );

int main(int argc,char **argv)
{
	

	int filedes1,filedes2;
	if(argc!=3)//checking for number of arguments
		{
			
			printf("\nThe correct format is ./myCompress <inputfilename> <outputfilename>\n");
		}
	else
		{
			printf("\nCorrect number of Arguments\n\n");
			strncpy(ipfile,argv[1],MAXSIZE-1);//Storing the input and output file name from arguments
			strncpy(opfile,argv[2],MAXSIZE-1);
			printf(" InputFile\t: %s\n OutputFile\t: %s\n",ipfile,opfile);

			filedes1=open(ipfile,O_RDONLY);

			if(filedes1==-1)
				{
					printf("\nCannot open file : %s\n",ipfile);
					printf("\nExiting now\n");
					exit(0);
				}

			filedes2=open(opfile,O_CREAT|O_TRUNC|O_RDWR,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

			if(filedes2>0)
			{       printf("\n Output file not there creating one now\n");
				
			}

			Compression(filedes1,filedes2);//Calling the function
			close(filedes1);
			close(filedes2);
			printf("\nProgram Successfully Compressed your file \n\n");
			clock_t start = clock();
			clock_t end= clock();
			printf("\nTime taken:%lf\n",(double)(end- start)*1000.0/CLOCKS_PER_SEC);


			return 0;
		}



}


void Compression(int fd1,int fd2)
{



	while(l==0)
	{
		if((n=read(fd1,&c,1)==0))
		{
			//Checks whether the file is empty
			if(i==0)
			{
				printf("\n*****The File is Empty. Nothing can be written*****\n");
				break;
			}
			else 
			{
				l=1;
				ch=c;
				writefile(fd1,fd2);
				break;
			}

		}
		else
		{
			writefile(fd1,fd2);

		}
		++i;
	}
}


void writefile(int fd1,int fd2)
{
		if((i==0)||(count<1))
		{
			if (c == 10)
				// checking for end line char and it assignes it to the ch 
			{
				w = write(fd2, &c, 1);
				ch=c;
			}
			else if (c == 32)// cheking for space and it assignes it to the ch

			{
				w = write(fd2, &c, 1);
				ch=c;
			}
// note ch is the previous read character 

			else if((c==one )||(c==zero))
			{//  start the count of zeros or ones 
				count=1;
				ch=c;
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
				if(ch==one )
				{
					for(j=0;j<count;j++)
					{
						w=write(fd2,&ch,1);
					}
					count=1;
				}
				else if(ch==zero)
				{
					for(j=0;j<count;j++)
					{
						w=write(fd2,&ch,1);
					}
					count=1;
				}
				if((c==one )||(c==zero)&&(l!=1))
				{
					ch=c;
				}
			}
			else if((count>=16))
			{
				sprintf(counter,"%d",count);
				int countsize=strlen(counter);
				if(ch==one )
				{
					w=write(fd2,&plus,1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,&plus,1);
					count=1;
					if((c==zero))
					{
						ch=c;
					}

				}
				else
				{
					w=write(fd2,&minus,1);
					w=write(fd2,(void *)(counter),countsize);
					w=write(fd2,&minus,1);
					count=1;
					if((c==one))
					{
						ch=c;
					}
				}
			}
			if((c==10)&&(l!=1))
			{
				w=write(fd2,&c,1);
				ch=c;
				count=1;
			}
			else if((c==32)&&(l!=1))
			{
				w=write(fd2,&c,1);
				ch=c;
				count=1;
			}
		}
}

/*
Note :
how to  get the cpu speed found at stackoverflow

*/
