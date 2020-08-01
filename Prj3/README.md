# Design and Implementation of Secondary Storage System

## Observation for problem 1:
When a client sends a request to connect to server, the server assigns a new thread to handle this request.
The newly assigned thread is given the access to streams for communicating with the client. After assigning the new thread,
the server from its while loop, again comes into accepting state. When a second request comes while first is still in process, 
the server accepts this requests and again assigns a new thread for processing it. In this way, multiple requests can be handled 
even when some requests are in process.


## Observation for problem 2:
In this program we implemented a directory listing server anda  lsclient. this provides the server with data in the form of an array of parameter to the ls program. the server forks a child to hable the request and prints the output to the client socket 

## Observation for problem 3:
In this we are using a client server to implement a physical disk. The disk is organized by tracks and sectors. This simulation stores the data to the actual disk in the form of a file.

## Observation for problem 4:
 The diskserver must be running for fserver to run and fserver to run fclient. This program implemented a file server system 
and uses the same dserver from the thrid program. It implements a single directory file system


## Observation for problem 5:
We must keep track of directory and file so that names can repeat and track of the current directory to print pwd command.
 mkdir and cd are like C and R of file names. similarly rmdir is like Delete command. 
 
