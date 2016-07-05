# makefile para a fila com prioridade
CC = gcc
CFLAGS = -ansi -Wall

OBJM = pqueue_dijkstra.o
HEADERS = pqueue_dijkstra.h

OBJECTS = $(OBJM) test1.o
EXES = test1

all:	$(EXES)

test1:	test1.o $(OBJM)
	$(CC) $(CFLAGS) test1.o $(OBJM) -o test1


$(OBJM):	$(HEADERS)

clean:
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f $(EXES)