#include "include/connection.h"
#include "include/server.h"

int main(int argc, char *argv[]) 
{
 	server();
 	
 	return 0;
}

int server()
{
	int server_sockfd, result;
	struct sockaddr_un server_address;
	
	unlink(SOCKET_NAME);
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (server_sockfd == -1)
	{
		perror("Failed to create a server socket");
		exit(1);
	}
	
	server_address.sun_family = AF_UNIX;
	if (!strcpy(server_address.sun_path, SOCKET_NAME))
	{
		perror("Failed to copy a server socket's name");
		exit(2);
	}
	
	result = bind(server_sockfd, (struct sockaddr *)&server_address,
				sizeof(server_address));
	if (result == -1)
	{
		perror("Failed to bind a name to a server socket");
		exit(3);
	}
	
	result = listen(server_sockfd, NCLIENTS);
	if (result == -1)
	{
		perror("Failed to listen for connections");
		exit(4);
	}
	
	write_to_journal("Server running");
	wait_for_data(server_sockfd);
	
	close(server_sockfd);
	
	return 0;
}

int wait_for_data(int server_sockfd)
{
	int client_sockfd, result;
	char buffer[MAX_MESSAGE_SIZE];
	
	while(1)
	{
		client_sockfd = accept(server_sockfd, NULL, NULL);
		if (client_sockfd == -1)
		{
			perror("Failed to accept a connection");
			return -1;
		}
		
		result = recv(client_sockfd, buffer, MAX_MESSAGE_SIZE, 0);
		if (result == -1)
		{
			perror("Failed to receive a message");
			close(client_sockfd);
			return -1;
		}
		
		result = strcmp(KILLER_MESSAGE, buffer);
		if (result == 0)
		{
			write_to_journal("Server is closed");
			close(client_sockfd);
			return 0;
		}
		else
		{
			write_to_journal(buffer);
		}
		
		close(client_sockfd);
	}
	
	write_to_journal("Server is closed");
	return 0;
}

int write_to_journal(char *message)
{
	char buffer[MAX_MESSAGE_SIZE];
	
	snprintf(buffer, MAX_MESSAGE_SIZE,
		"date >> %s; echo '\%s\n\' >> %s", JOURNAL, message, JOURNAL);
	system(buffer);
	
	return 0;
}
