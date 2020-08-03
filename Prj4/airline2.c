#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

int passengers;
int baggage;
int security;
int flightAttend;

pthread_mutex_t mutex;
sem_t P;
sem_t B;
sem_t S;
sem_t F;
pthread_attr_t attr;
pthread_attr_t attr2;
pthread_attr_t attr3;
pthread_attr_t attr4;
pthread_attr_t attr5;

void init() 
{
	 pthread_mutex_init(&mutex, NULL);
	sem_init(&P,0,1);
	
	sem_init(&B,0,0);
	sem_init(&S,0,0);
	sem_init(&F,0,0);
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
		pthread_attr_init(&attr2);
	pthread_attr_setscope(&attr2, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_JOINABLE);
	
		pthread_attr_init(&attr3);
	pthread_attr_setscope(&attr3, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr3, PTHREAD_CREATE_JOINABLE);
	
		pthread_attr_init(&attr4);
	pthread_attr_setscope(&attr4, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr4, PTHREAD_CREATE_JOINABLE);
	
		pthread_attr_init(&attr5);
	pthread_attr_setscope(&attr5, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr5, PTHREAD_CREATE_JOINABLE);
}

void *passenger (void *args){
//sem_wait(&P);

int n=passengers,i;
  bool arr[10]={0};
  time_t t;
  srand((unsigned)time(&t));
  for(i=0;i<n;++i)
  {
    int r=rand()% passengers;
    if(!arr[r]) {
    printf("Passenger #%d arrived at the terminal.\n", r + 1);
	} else {
      i--;
    arr[r]=1;   
	}	
  }
		 pthread_mutex_lock(&mutex);
		 
}

void *baggagex (void *args)
{
	  int q=passengers,w;
  int arrq[10]={0};
  time_t qw;
  srand((unsigned)time(&qw));
  for(w=0;w<q;++w)
  {
    int z=rand()% passengers;
    if(!arrq[z]){
  printf("Passenger #%d waiting at baggage processing for a handler.\n", z + 1);
	}  else{
      q--;
    arrq[z]=1;    
  }
}
}
void *securityscreen (void *args)
{
 int nx=passengers,io;
  int arra[10]={0};
  time_t tp;
  srand((unsigned)time(&tp));
  for(io=0;io<nx;++io)
  {
    int r1=rand()% passengers;
    if(!arra[r1]){
    printf("Passenger #%d is waiting to be screened by a screener.\n", r1 + 1);
	} else
      io--;{
    arra[r1]=1;    
  }

}
}
void *planeattend (void *args)
{
int n3=passengers,i1;
  int arr2[10]={0};
  time_t t9;
  srand((unsigned)time(&t9));
  for(i1=0;i1<n3;++i1)
  {
    int rm=rand()% passengers;
    if(!arr2[rm]){
    printf("Passenger #%d is waiting to board the plane by an attendant.\n", rm + 1);
  }else{
      i1--;
    arr2[rm]=1;    
  }
}
}
void *relaxed (void *args)
{
 int ny=passengers,iy;
  int arro[10]={0};
  time_t tkl;
  srand((unsigned)time(&tkl));
  for(iy=0;iy<ny;++iy)
  {
    int ryg=rand()% passengers;
    if(!arro[ryg]){
    printf("Passenger #%d has been seated and relaxes.\n", ryg + 1);
  }else{
      iy--;
    arro[ryg]=1;    
  }
}
}
int main(int argc, char **argv) {

	if (argc != 5)//checking for number of arguments
	{
		printf("\nHey argument must be 5!!");
		printf("\nThe correct format is ./air <# of Passengers> <# of Baggage handlers> <# of Security screeners> <# of Flight attendents>\n");

	} else {
		passengers = atoi(argv[1]);
		baggage = atoi(argv[2]);
		security = atoi(argv[3]);
		flightAttend = atoi(argv[4]);

		init();

		pthread_t pass;
		pthread_t bagg;
		pthread_t secr;
		pthread_t attd;
		pthread_t relax;
		//threads created , waited by join to perform the given task for the number of days 
		
		pthread_create(&pass,&attr,passenger,NULL);
		pthread_create(&bagg,&attr,baggagex,NULL);
		pthread_create(&secr,&attr,securityscreen,NULL);
		pthread_create(&attd,&attr,planeattend,NULL);
		pthread_create(&relax,&attr,relaxed,NULL);
		
		pthread_join(pass,NULL);
		pthread_join(bagg,NULL);
		pthread_join(secr,NULL);
		pthread_join(attd,NULL);
		pthread_join(relax,NULL);

	exit(0);

	}
}

