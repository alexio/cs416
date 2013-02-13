CC = gcc
CCFLAGS = -g -Wall

all: warshall_tc

debug:
	make DEBUG=TRUE
	
warshall_tc: main.o operations.o
	$(CC) $(CCFLAGS) -o sl main.o operations.o

main.o: main.c
	$(CC) $(CCFLAGS) -c main.c
	
operations.o: operations.c operations.h
	$(CC) $(CCFLAGS) -c operations.c
	
ifeq ($(DEBUG), TRUE)
CCFLAGS += -g
endif

clean:
	rm -f warshall_tc
	rm -f *.o

