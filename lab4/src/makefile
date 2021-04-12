CC=gcc
CFLAGS=-I.

all: process_memory parallel_sum

parallel_sum: parallel_sum.c utils.o sum.o
	$(CC) utils.o sum.o parallel_sum.c -o parallel_sum.out $$(CFLAGS) -pthread -W

sum.o : sum.c sum.h
	$(CC) -c sum.c -o sum.o $$(CFLAGS)

find_min_max.o: utils.o find_min_max.c find_min_max.h
	$(CC) -c find_min_max.c -o find_min_max.o $$(CFLAGS)

utils.o: utils.c utils.h
	$(CC) -c utils.c -o utils.o $$(CFLAGS)

process_memory: process_memory.c
	$(CC) process_memory.c -o process_memory.out -W $$(CFLAGS)

clear:
	rm *.o
