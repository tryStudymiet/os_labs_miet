CC=gcc

all: client server
	
client: client.c utFactorials
	$(CC) client.c utFactorials.o -o client.out

server: server.c utFactorials
	$(CC) server.c utFactorials.o -lpthread  -o server.out

utFactorials: utFactorials.c utFactorials.h
	$(CC) -c utFactorials.c -o utFactorials.o

clear:
	rm *.o *.out
