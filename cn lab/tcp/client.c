#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
void main(){
	int clientsock,error;
	struct sockaddr_in client;
	
	clientsock=socket(AF_INET,SOCK_STREAM,0);
	
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=htons(6265);
	
	error=connect(clientsock,(struct sockaddr*)&client,sizeof(client));
	if(error==-1){
		printf("connection error\n");
	}
	printf("connection succesfull\n");
	int i=1;
	while(i){
		char buffer[100];
		char response[100];
		printf("client:");
		fgets(buffer,100,stdin);
	
		error=send(clientsock,buffer,100,0);
			if(error==-1){
			printf("sending error\n");
		}
		recv(clientsock,response,100,0);
		printf("server:%s",response);
		memset(response,0,100);
		if(strncmp(buffer,"exit",4)==0){
			i=0;
		}
	}
	close(clientsock);
}
