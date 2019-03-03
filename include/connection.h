#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SOCKET_NAME      "/tmp/connection.sock"
#define JOURNAL          "/tmp/journal.txt"
#define KILLER_MESSAGE   "Hande hoch"  
#define MAX_MESSAGE_SIZE 100

#endif
