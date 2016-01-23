#
# To compile, type "make" or make "all"
# To remove files, type "make clean"
#
OBJS = server.o request.o cs537.o client.o
TARGET = server

CC = gcc
CFLAGS = -g -Wall

LIBS = -lpthread 

.SUFFIXES: .c .o 

all: server client output.cgi

server: server.o request.o cs537.o queue.o
	$(CC) $(CFLAGS) -o server server.o request.o cs537.o  queue.o $(LIBS)

client: client.o cs537.o
	$(CC) $(CFLAGS) -o client client.o cs537.o $(LIBS)

output.cgi: output.c
	$(CC) $(CFLAGS) -o output.cgi output.c $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBS)

clean:
	-rm -f $(OBJS) queue.o server client output.cgi
