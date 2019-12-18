all: client server
.PHONY:all

client:client.o
	cc -o client client.o
server:server.o
	cc -o server server.o

client.o:client.c
	cc -c client.c
server.o:server.c
	cc -c server.c

.PHONY:clean
clean:
	rm client server client.o server.o
