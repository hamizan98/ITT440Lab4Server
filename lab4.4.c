#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#include<stdlib.h>

int main(int argc , char *argv[])
{
	char buf[100];
	int socket_desc, new_socket, k;
	socklen_t len;
	struct sockaddr_in server, client;
	char *message;
	

	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		exit(1);
	}

	//Listen
	k = listen(socket_desc, 3);
	
	if(k == -1)
	{
		printf("Error in listening");
		exit(1);
	}
	
	len = sizeof(client);

	new_socket = accept(socket_desc,(struct sockaddr*)&client,&len);
	if(new_socket == -1)
	{
		printf("Error in temporary socket creation");
		exit(1);
	}
	
	while(1)
	{

		k = recv(new_socket, buf, 100, 0);
		
		if(k == -1)
		{
			printf("Error in receiving");
			exit(1);
		}
			printf("Client: %s",buf); //Mesej dari client
			printf("\nServer: "); //Mesej untuk client
			fgets(buf,100,stdin);
			if(strncmp(buf,"bye",3)==0)
			break;
			k=send(new_socket,buf,100,0);
			if(k==-1)
			{
			printf("Error in sending");
			exit(1);
		}
	}
	close(new_socket);
	exit(0);
	return 0;
}
