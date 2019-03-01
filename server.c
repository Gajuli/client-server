#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() 
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
/*удаляем старые, создаем новый*/
	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
/*присвоить имя*/
	server_address.sun_family = AF_UNIX;
 	strcpy(server_address.sun_path, "server_socket");
 	server_len = sizeof(server_address);
 	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
/*ждемс*/
	system("date>>jj.txt"); system("echo 'сервер запущен\n'>>jj.txt");
	listen(server_sockfd, 5);
 	while(1) 
	{
  		char message[40];
		printf("server waiting\n");
/*принимаем запрос*/
		client_len = sizeof(client_address);
  		client_sockfd = accept(server_sockfd,
   		(struct sockaddr *)&client_address, &client_len);
/*читаем данные клиента*/
		client_sockfd
		:
		
		//memset(message,' ',40);
  		read(client_sockfd, &message, 40);
  		//printf("%s", message);
		if (!strcmp(message,"halt")) 
		{
			close(server_sockfd); system("date>>jj.txt"); 
			system("echo 'работа завершена\n'>>jj.txt"); 
			break;
		}
		else
		{
			int fs1,k;
			system("date>>jj.txt"); 
			fs1 = open("jj.txt", O_WRONLY);
			k=lseek(fs1, 0,SEEK_END);
			int i=0; while (message[i]!='\00') i++;
			write(fs1, message, i);	system("echo '\n'>>jj.txt");
			close(fs1);
		}
  		//write(client_sockfd, &message, 40);
  		close(client_sockfd);
		
 	}
}
