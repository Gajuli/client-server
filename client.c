#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char message[40]={0};
	

	/*создается соккет клиента*/
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	/**/
	address.sun_family = AF_UNIX;
 	strcpy(address.sun_path, "server_socket");
	len = sizeof(address);
	/*коннектимс*/
	result = connect(sockfd, (struct sockaddr *)&address, len);
 	if (result == -1) 
	{
  		perror("servak ne zapush'en");
  		exit(1);
 	}
	sockfd
	:
		scanf("%s",message);
 		write(sockfd, &message, 40);
 		//read(sockfd, &message, 40);
 		//printf("char from server = %s\n", message);
 		close(sockfd);
	
 	exit(0);
}

