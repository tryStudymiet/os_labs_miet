CC = gcc 
TO_F = ./outs/

all: main

main: main_client main_server

main_client: main_client.c
	$(CC) main_client.c -o $(TO_F)main_client.out

main_server: main_server.c
	$(CC) main_server.c -o $(TO_F)main_server.out

clear: *.o
