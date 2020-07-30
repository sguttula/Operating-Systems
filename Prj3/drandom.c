#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#define SIZE 1024
#define BS 128
char buf[SIZE];

#define TIME_PORT 9005

/*
This client should query the disk for its size (using the I command), and then generate
a series of N random requests to the disk. Each request should randomly be W or R, and the cylinder number
and sector number should be randomly chosen from the valid range for that disk

*/

int main(int argc,
         char *argv[])
{
  int sockfd;
  int nread;
  struct sockaddr_in serv_addr;
  struct hostent *host;
  uint16_t serv_port;
  char *ip;


  if (argc != 5)
  {
    fprintf(stderr,"\nUsage: /.drandom <IP> <PORT> <N> <SEED>\n\n");
    exit(1);
  }
  ip=argv[1];
  serv_port=atoi(argv[2]);

  //create endpoint 
  if ((sockfd = socket(AF_INET,SOCK_STREAM, 0))< 0) {
    perror(NULL);
    exit(2);
  }

  char *cmd,*tmp,*tp,ch,*result,chr;
  int i,j,tt,p_number,N,seed,trk,sec;
  char read_or_write[]={'r','w'};

   p_number= atoi(argv[2]);
   N=atoi(argv[3]);
   seed=atoi(argv[4]);

  //connect to server
  serv_addr.sin_family = AF_INET;
  host = gethostbyname(argv[1]);
  memcpy(&serv_addr.sin_addr.s_addr, host->h_addr, host->h_length);
  serv_addr.sin_port =
            htons(serv_port);
  if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))< 0) {
    perror(NULL);
    exit(3);
  }

  


 //Generating the command from the random client and sending it to the server for executing and prints request and response as w or r
  	 
    srand(seed);
    cmd = (char *)malloc(200*sizeof(char));
    write(sockfd,"i",1);
    result = (char *)malloc(200*sizeof(char));
    	nread = read(sockfd,result,150);
    	result[nread]='\0';

  sscanf(result,"%d %d",&trk,&sec);

  	 while(N>0)
  	 {

  		 switch(rand()%2)
  		 {
  		 case 0:	//This case is executed if the generated command is Write
  			 	 	 	 sprintf(cmd,"%c %d %d",'w',rand()%trk+1,rand()%sec+1);
  			 	 	 	 tp =(char *)malloc(BS*sizeof(char));
  			 		 	 for(i=0;i<BS;i++) //random character generated to write to the file. The generated value will be 128
  			 		 	 {
  			 		 		tt = rand()%57;
  			 		 		tt= tt+65;
  			 		 		ch= (char)tt;
  			 		 		tp[i]=ch;
  			 		 	 }
  			 		 	 	 tp[i]='\0';
  			 		 		tmp =(char *)malloc((BS+3)*sizeof(char));
  			 		 		sprintf(tmp," %ld %s",strlen(tp),tp);
  			 		 		strcat(cmd,tmp);
  			 		 		free(tp);
  			 		 		free(tmp);
  			 		 		printf("Request:%s\n","W");

  			 		 		 write(sockfd,cmd,strlen(cmd));
  			 		 		strcpy(cmd,"\0");
  			 		 		break;
  		 case 1: 		sprintf(cmd,"%c %d %d",'r',rand()%trk+1,rand()%sec+1); //This case is executed if the generated command is read
  		 	 	 	 	 	 printf("Request:%s\n","R");
  		 	 	 	 	 	 write(sockfd,cmd,strlen(cmd));
  		 	 	 	 	 	 strcpy(cmd,"\0");
  			 	 	 break;
  		 default:
  			 	 	 printf("Default\n");

  		 }
  
  	result = (char *)malloc(200*sizeof(char));
  	nread = read(sockfd,result,150);
  	result[nread]='\0';
  	printf("Response:%s\n",result);
  	free(result);
  	N--;
  	 }
    close(sockfd);
    exit(0);
  }
