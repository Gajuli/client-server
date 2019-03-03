CC=gcc

all: client server
	
clean:
	rm -rf client server *.o
	
client: client.c \
		include/connection.h
	$(CC) -o client client.c
	
server: server.c \
		include/server.h \
		include/connection.h
	$(CC) -o server server.c
