# Realizing Concurrency using Unix processes and threads

## 1 mycompress
This program reads in 2 files compress it sequentially 

## 2 mydecompress
This program reads in 2 files and decompress it sequentially

## 3 forkcompress
This program reads in 2 files and compress it but done with forks 

## 4 pipecompress
This program reads in 2 files and compress it  but  this is done with pipes rather than doing it sequentially pr forks

## 5 parkfork
This programs does the same compression from program one but the file now will be divided into equal chunks

## 6 minishell
This program creates your own mini unix shell but with limited usage


## 7 moreshell
This program creates your own mini unix shell just as the previous program but this time it has
a little bit more power then before 


## 8 dupeshell
This program creates your own mini unix shell like before but this time were using pipes and  the dup2 system call to redirect the output 


## 9 posix threads
This program checks the time speed of the threads,  also we didnt now if it was to be cpu clock or "wall clock" since it does specify which one 
at cpu speed 

Time complexity:
Same for both sequential and fork, respectively;
Time taken: 0.001000, 
Time taken: 0.001000

