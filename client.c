#include "include/connection.h"

int main(int argc, char *argv[]) 
{
	int sockfd, result;
	struct sockaddr_un address;
	char message[MAX_MESSAGE_SIZE];
	
	if (argc < 2)
	{
		perror("Message is required. Usage: ./client \'message\'\n");
		exit(EXIT_FAILURE);
	}
	
	if (!strncpy(message, argv[1], MAX_MESSAGE_SIZE))
	{
		perror("Failed to copy a message");
		exit(EXIT_FAILURE);
	}
	
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("Failed to create a socket");
		exit(EXIT_FAILURE);
	}
	
	address.sun_family = AF_UNIX;
 	if(!strcpy(address.sun_path, SOCKET_NAME))
 	{
		perror("Failed to copy a socket's name");
		exit(EXIT_FAILURE);
	}
 	
	result = connect(sockfd, (struct sockaddr *)&address,
				sizeof(address));
 	if (result == -1) 
	{
  		perror("Connection failed");
  		exit(EXIT_FAILURE);
 	}
 	
	result = send(sockfd, message, sizeof(message), 0);
	if (result == -1)
	{
		perror("Failed to send a data");
		exit(EXIT_FAILURE);
	}
	
	close(sockfd);
	
 	return 0;
}

