CC=gcc
CFLAGS=-I.

all : sequential_min_max parallel_min_max

sequential_min_max : utils.o find_min_max.o find_min_max.h sequential_min_max.c
	$(CC) -o sequential_min_maxMF.out find_min_max.o utils.o sequential_min_max.c $(CFLAGS)

parallel_min_max : utils.o find_min_max.o find_min_max.h parallel_min_max.c
	$(CC) -o parallel_min_maxMF.out utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

utils.o : utils.h utils.c
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h find_min_max.c
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

lab3t5: lab3t5.c
	$(CC) -o lab3t5.out lab3t5.c

clean :
	rm *.o
