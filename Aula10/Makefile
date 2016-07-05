# makefile para a arvore ABP (Arvore Binaria de Pesquisa)
CC = gcc
CFLAGS = -ansi -Wall -g

OBJM = queue.o stack.o abp.o
HEADERS = queue.h stack.h abp.h

OBJECTS = $(OBJM) testabp.o simabp.o
EXES = tabp sabp

all:	$(EXES)

tabp:	testabp.o $(OBJM)
	$(CC) $(CFLAGS) testabp.o $(OBJM) -o tabp

sabp:	simabp.o $(OBJM)
	$(CC) $(CFLAGS) simabp.o $(OBJM) -o sabp

$(OBJM):	$(HEADERS)

clean:
	rm -f $(OBJECTS) *~

cleanall:	clean
	rm -f $(EXES)
