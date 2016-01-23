#include "cs537.h"
#include "request.h"
#include "queue.h"
#include <errno.h>
#include <limits.h>

// 
// server.c: A very, very simple web server
//
// To run:
//  server <portnum (above 2000)> <number of threads> <number of buffers>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c

int parse(char *str) {
	long val;
	char *temp;
	val = strtol(str, &temp, 10);
	if (val > UINT_MAX || val <= 0 || errno == ERANGE || temp[0] != '\0') {
		return -1;
	} else {
		return (int) val;
	}
}

void getargs(int *port, int *threads, int *buffers, int argc, char *argv[]) {
    if (argc != 4) {		
		fprintf(stderr, "Usage: %s <portnum> <threads> <buffers>\n", argv[0]);
		exit(1);
    }
    *port    = parse(argv[1]);
	*threads = parse(argv[2]);
	*buffers = parse(argv[3]);
	if (*port == -1 || *threads == -1 || *buffers == -1) {
		fprintf(stderr, "Usage: %s <portnum> <threads> <buffers>\n", argv[0]);
		exit(1);
	}
}

pthread_mutex_t queue_lock;
pthread_cond_t empty, fill;
Queue Q;

void *worker_thread(void *arg) {
	while (1) {
		Pthread_mutex_lock(&queue_lock);
		while (Q.size == 0) {
			Pthread_cond_wait(&fill, &queue_lock);
		}
		int connfd;
		connfd = dequeue(&Q);
		Pthread_cond_signal(&empty);
		Pthread_mutex_unlock(&queue_lock);

		requestHandle(connfd);
		Close(connfd);
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	int listenfd, connfd, port, clientlen, threads, max;
	struct sockaddr_in clientaddr;
	pthread_t *threads_arr;
	
	getargs(&port, &threads, &max, argc, argv);
	
	queue_init(&Q);
	Pthread_mutex_init(&queue_lock, NULL);
	Pthread_cond_init(&empty, NULL);
	Pthread_cond_init(&fill, NULL);

	threads_arr = (pthread_t *) malloc(sizeof(pthread_t) * threads);
	if (threads_arr == NULL) {
		unix_error("malloc error");
	}	

	int i;
	for (i = 0; i < threads; i++) {
    	Pthread_create(&(threads_arr[i]), NULL, worker_thread, NULL);
	}

	listenfd = Open_listenfd(port);
	while (1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);
		
		Pthread_mutex_lock(&queue_lock);
		while (Q.size ==  max) {
			Pthread_cond_wait(&empty, &queue_lock);
		}
		enqueue(&Q, connfd);
		Pthread_cond_signal(&fill);
		Pthread_mutex_unlock(&queue_lock);
	}
}
