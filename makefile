CC = gcc
CCFLAGS = -g -Wall -pthread

all: warshall_tc

debug:
	make DEBUG=TRUE
	
warshall_tc: wtc.o operations.o wtc_thr.o wtc_proc.o
	$(CC) $(CCFLAGS) -o warshall_tc wtc.o operations.o wtc_thr.o wtc_proc.o

wtc.o: wtc.c
	$(CC) $(CCFLAGS) -c wtc.c
	
operations.o: operations.c operations.h
	$(CC) $(CCFLAGS) -c operations.c
	
wtc_thr.o: wtc_thr.c
	$(CC) $(CCFLAGS) -c wtc_thr.c

wtc_proc.o: wtc_proc.c
	$(CC) $(CCFLAGS) -c wtc_proc.c

ifeq ($(DEBUG), TRUE)
CCFLAGS += -g
endif

clean:
	rm -f warshall_tc
	rm -f *.o
>>>>>>> 6cd48f61817ca138ecd212e402f73d9082773aa9
