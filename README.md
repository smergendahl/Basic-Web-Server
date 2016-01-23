# Basic-Web-Server
A Scaleable Multi-Threaded Web Server
Created by Sam Mergendahl (github.com/smergendahl) and Colin Samplawski (github.com/colinski)

We created a simple queue using a linked list to store the requests. After creating the threads, the worker threads cond_wait on the queue being empty, and the producer thread cond_wait on the queue being "full" (at the max size). After waking up a worker dequeues a request and handles it, while the producer thread enqueues a request.

# Discription of Files:
server.c: Contains main() for the basic web server.

request.c: Performs most of the work for handling requests in the basic web server. All procedures in this file begin with the string “request”.

cs537.c: Contains wrapper functions for the system calls invoked by the basic web server and client. The convention is to capitalize the first letter of each routine.

client.c: Contains main() and the support routines for the very simple web client.

output.c: Code for a CGI program. Basically, it spins for a fixed amount of time, which was useful in testing various aspects of the server.

queue.c: This is a file that contains all the needed information for the queue data structure.
