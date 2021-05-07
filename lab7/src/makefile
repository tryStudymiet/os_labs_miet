CC = gcc 
TO_F = ./outs/

all: tcp udp

tcp: tcpclient tcpserver

udp: udpclient udpserver

tcpclient: tcpclient.c
	$(CC) tcpclient.c -o $(TO_F)tcpclient.out

tcpserver: tcpserver.c
	$(CC) tcpserver.c -o $(TO_F)tcpserver.out

udpclient: udpclient.c
	$(CC) udpclient.c -o $(TO_F)udpclient.out

udpserver: udpserver.c
	$(CC) udpserver.c -o $(TO_F)udpserver.out

clear: *.o
