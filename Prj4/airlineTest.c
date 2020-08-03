//#include "thread_107.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_DINERS 100
//#define NUM_B, NUM_S, NUM_F 1
/* Macros to conveniently refer to forks to left and right of each person */
#define LEFT(philNum) (philNum)

/*#define RIGHT(philNum) (((philNum)+1) % NUM_DINERS)*/

/*
 * Our main is creates a semaphore for every fork in an unlocked state
 * (one philosopher can immediately acquire each fork) and sets up the
 * numEating semaphore to only allow N-1 philosophers to try and grab
 * their forks. Each philosopher runs its own thread. They should
 * finish after getting their fill of spaghetti. By running with the

 * -v flag, it will include the trace output from the thread library.
  */
void main(int argc, char **argv)
{
	int i;
	char name[32];
	sem_t waiting[argv[1]];
	sem_t line;
	//InitThreadPackage(verbose);
for (i = 0; i < argv[1]; i++) { // Create all fork semaphores
 sprintf(name, "Fork %d", i);
waiting[i] = SemaphoreNew(name, 1); // all forks start available
}
line = SemaphoreNew(“Num Eating”, argv[1] - 1);

for (i = 0; i < argv[1]; i++) { // Create all philosopher threads
sprintf(name, "Philosopher %d", i);
ThreadNew(name, Philosopher, 3, numEating, waiting[LEFT(i)]);
}
RunAllThreads();


	printf("%s has been seated and relaxes.\n", ThreadName());
}
static void passenger(Semaphore line, Semaphore waitTime){
	 int i;
 for (i = 0; i < NUM_B; i++) {
baggageHandeler(line, waitTime);
securityScreeners(line, waitTime);
flightAttendants(line, waitTime);
//Eat(numEating, leftFork, rightFork);
 }
}
static baggageHandeler(Semaphore line, Semaphore waitTime) {
	SemaphoreWait(line); // wait until can try to get forks
SemaphoreWait(waitTime);
	printf("%s waiting at baggage processing for a handler.\n", ThreadName());
	RandomDelay(10000,50000); 
	SemaphoreSignal(line); // let go
SemaphoreSignal(waitTime);
}
static securityScreeners(Semaphore line, Semaphore waitTime) {
	SemaphoreWait(line); // wait until can try to get forks
SemaphoreWait(waitTime);
	printf("%s waiting to be screened by a screener.\n", ThreadName());
	RandomDelay(10000,50000); 
	SemaphoreSignal(line); // let go
SemaphoreSignal(waitTime);
}
static flightAttendants(Semaphore line, Semaphore waitTime) {
	SemaphoreWait(line); // wait until can try to get forks
SemaphoreWait(waitTime);
	printf("%s waiting to board the plane by an attendant.\n", ThreadName());
	RandomDelay(10000,50000); 
	SemaphoreSignal(line); // let go
SemaphoreSignal(waitTime);
}