CC = gcc
CCFLAGS = -g -Wall -lpthread

all: warshall_tc

debug:
	make DEBUG=TRUE
	
warshall_tc: wtc.o operations.o
	$(CC) $(CCFLAGS) -o warshall_tc wtc.o operations.o

wtc.o: wtc.c
	$(CC) $(CCFLAGS) -c wtc.c
	
operations.o: wtc_proc.c operations.h
	$(CC) $(CCFLAGS) -c wtc_proc.c
	
ifeq ($(DEBUG), TRUE)
CCFLAGS += -g
endif

clean:
	rm -f warshall_tc
	rm -f *.o

