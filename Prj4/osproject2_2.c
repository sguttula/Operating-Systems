#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
typedef int buffer_item;
#define BUFFER_SIZE 5
#define RAND_DIVISOR 100000000
#define TRUE 1
#include <unistd.h>

pthread_mutex_t mutex;
/* the semaphores */
sem_t full, empty;
/* the buffer */
buffer_item buffer[BUFFER_SIZE];
/* buffer counter */
int counter;


void init() {

   /* Create the mutex lock */
   pthread_mutex_init(&mutex, NULL);

   /* Create the full semaphore and initialize to 0 */
   sem_init(&full, 0, 0);

   /* Create the empty semaphore and initialize to BUFFER_SIZE */
   sem_init(&empty, 0, BUFFER_SIZE);


   /* init buffer */
   counter = 0;

    /* Required to schedule thread independently.*/
  pthread_attr_init(&attr);
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  /* end to schedule thread independently */
}



/* Producer Thread */
void *producer(void *param) {
   buffer_item item;

   while(TRUE) {
      /* sleep for a random period of time */
      int rNum = rand() / RAND_DIVISOR;
      sleep(rNum);

      /* generate a random character */
      item = 'A' + (random() % 26);

      /* acquire the empty lock */
      sem_wait(&empty);
      /* acquire the mutex lock */
      pthread_mutex_lock(&mutex);

      if(insert_item(item)) {
         fprintf(stderr, " Producer report error condition\n");
      }
      else {
         printf("producer produced %d\n", item);
      }
      /* release the mutex lock */
      pthread_mutex_unlock(&mutex);
      /* signal full */
      sem_post(&full);
   }
}

/* Consumer Thread */
void *consumer(void *param) {
   buffer_item item;

   while(TRUE) {
      /* sleep for a random period of time */
      int rNum = rand() / RAND_DIVISOR;
      sleep(rNum);

      /* aquire the full lock */
      sem_wait(&full);
      /* aquire the mutex lock */
      pthread_mutex_lock(&mutex);
      if(remove_item(&item)) {
         fprintf(stderr, "Consumer report error condition\n");
      }
      else {
         printf("consumer consumed %d\n", item);
      }
      /* release the mutex lock */
      pthread_mutex_unlock(&mutex);
      /* signal empty */
      sem_post(&empty);
   }
}

/* Add an item to the buffer */
int insert_item(buffer_item item) {
   /* When the buffer is not full add the item
      and increment the counter*/
   if(counter < BUFFER_SIZE) {
      buffer[counter] = item;
      counter++;
      return 0;
   }
   else { /* Error the buffer is full */
      return -1;
   }
}

/* Remove an item from the buffer */
int remove_item(buffer_item *item) {
   /* When the buffer is not empty remove the item
      and decrement the counter */
   if(counter > 0) {
      *item = buffer[(counter-1)];
      counter--;
      return 0;
   }
   else { /* Error buffer empty */
      return -1;
   }
}



main() {

  int r = 0;
  int i;
  sem_t sem1;
  int shmid;              /* shared memory ID */
  pthread_t p;      /* process id for thread 1 */
  pthread_t c;      /* process id for thread 2 */
  pthread_attr_t attr; /* attribute pointer array */

  init(); 

  fflush(stdout);


  /* Create the threads */
  pthread_create(&p, &attr, &producer, NULL);
  pthread_create(&c, &attr, &consumer, NULL);

  /* Wait for the threads to finish */
  pthread_join(p, NULL);
  pthread_join(c, NULL);

  sleep(30);
  exit(0);
}