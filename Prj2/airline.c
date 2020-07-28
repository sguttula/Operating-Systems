#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

int passengers;
int baggage;
int security;
int flightAttend;

/*
int p = 1;
int b = 1;
int s = 1;
int fa = 1;
*/

sem_t P;
sem_t B;
sem_t S;
sem_t F;
pthread_attr_t attr;
int a = 1;
int pace;
int b_q = 1;

void init() 
{
	sem_init(&P,0,1);
	sem_init(&B,0,0);
	sem_init(&S,0,0);
	sem_init(&F,0,0);
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
}

void *passenger (void *args){
	//while(a <= pace) 
		for(int i = 0 ; i < passengers ; i++) {
			printf("Passenger #%d arrived at the terminal.\n", i + 1);
		}
		for(int i = 0 ; i < passengers/*baggage*/ ; i++) {
			//sem_wait(&B);
			printf("Passenger #%d waiting at baggage processing for a handler.\n", i + 1);
			//sem_post(&B);
			baggage++;
		}
		
		//b++;
		for(int i = 0 ; i < passengers/*security*/; i++) {
			//sem_wait(&S);
		printf("Passenger #%d is waiting to be screened by a screener.\n", i + 1);
	}
	//s++;
	for(int i = 0 ; i < passengers/*flightAttend*/ ; i++) {
		//sem_wait(&F);
		printf("Passenger #%d is waiting to board the plane by an attendant.\n", i + 1);
	}
	//fa++;
	for(int i = 0 ; i < passengers ; i++) {
			printf("Passenger #%d has been seated and relaxes.\n", i + 1);
			//sem_post(&P);
		}
		//a++;
	
		
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
		//threads created , waited by join to perform the given task for the number of days 
		
		pthread_create(&pass,&attr,passenger,NULL);
		
		pthread_join(pass,NULL);

	exit(0);

	}
}


