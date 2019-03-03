#ifndef SERVER_H_
#define SERVER_H_

#include <fcntl.h>

#define NCLIENTS 1

int demonize();
int server();
int wait_for_data(int server_sockfd);
int write_to_journal(char *message);

#endif
