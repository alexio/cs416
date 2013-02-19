CC = gcc
CCFLAGS = -g -Wall -lpthread

all: warshall_tc

debug:
	make DEBUG=TRUE
	
warshall_tc: wtc.o operations.o
	$(CC) $(CCFLAGS) -o warshall_tc wtc.o operations.o

wtc.o: wtc.c
	$(CC) $(CCFLAGS) -c wtc.c
	
operations.o: operations.h wtc_thr.c
	$(CC) $(CCFLAGS) -c wtc_thr.c
	
ifeq ($(DEBUG), TRUE)
CCFLAGS += -g
endif

clean:
	rm -f warshall_tc
	rm -f *.o

