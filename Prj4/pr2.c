#define REINDEER 9 /* max # of reindeer */
#define ELVES 3 /* size of elf group */
Semaphores
 only_elves = 3, /* 3 go to Santa */
 emutex = 1, /* update elf_ct */
 rmutex = 1, /* update rein_ct */
 rein_wait = 0, /* block early arrivals back from islands */
 sleigh = 0, /* all reindeer wait
 around the sleigh */
 done = 0, /* toys all delivered*/
 santa_signal = 0,/* 1st 2 elves wait on this outside Santa's shop */
 santa = 0, /* Santa sleeps on this blocked semaphore */
 problem = 0, /* wait to pose the question to Santa */
 elf_done = 0; /* receive reply */
Shared integers
 rein_ct = 0; /* # of reindeer back */
 elf_ct = 0; /* # of elves w/problem */
Local Integers
 i; /* for loop variable */
/* Reindeer Process */
for (;;){
 tan on the beaches in the Pacific
 until Christmas is close
 P(rmutex)
 rein_ct++
 if (rein_ct == REINDEER) {
 V(rmutex)
 V(santa)
 }
 else {
 V(rmutex)
 
 P(rein_wait)
 }
 /* all reindeer waiting to be
 attached to the sleigh */
 P(sleigh)
 fly off to deliver the toys
 P(done)
 head back to the Pacific islands
} /* end "forever" loop */
/* Elf Process */
for (;;){
 P(only_elves) /* only 3 elves "in"*/
 P(emutex)
 elf_ct++
 if (elf_ct == ELVES){
 V(emutex)
 V(santa) /* 3rd elf-wakes Santa */
 }
 else {
 V(emutex)
 P(santa_signal) /* wait outside
 Santa's shop door */
 }
 P(problem)
 ask question /* Santa woke elf up*/
 P(elf_done)
 V(only_elves)
} /* end "forever" loop */

for(;;){
 P(santa) /* Santa "rests" */
 /* mutual exclusion is not needed on
 rein_ct because if it is not equal
 to REINDEER, then elves woke up
 Santa */
 if (rein_ct == REINDEER){
 P(rmutex)
 rein_ct = 0 /* reset while reindeer blocked */
 V(rmutex);
 for (i = 0; i < REINDEER - 1; i++)
 V(rein_wait)
 for (i = 0; i < REINDEER; i++)
 V(sleigh)
 deliver all the toys and return
 for (i = 0; i < REINDEER; i++)
 V(done)
 }
 else { /* 3 elves have arrived */
 for (i = 0; i < ELVES - 1; i++)
 V(santa_signal)
 
 P(emutex)
 elf_ct = 0
 V(emutex)
 for (i = 0; i < ELVES; i++){
 V(problem)
 answer that question
 V(elf_done)
 }
 }
} /* end "forever" loop */
