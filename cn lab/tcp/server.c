#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void main(){
	int serversock,clientsock,error;
	struct sockaddr_in server,client;
	
	serversock=socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(6265);
	
	error=bind(serversock,(struct sockaddr*)&server,sizeof(server));
	if(error==-1){
		printf("error in binding\n");
	}
	
	error=listen(serversock,1);
	if(error==-1){
		printf("error in listening\n");
	}
	socklen_t len=sizeof(client);
	clientsock=accept(serversock,(struct sockaddr*)&client,&len);
	if(clientsock==-1){
		printf("error in binding\n");
	}
	int i=1;
	while(i){
		char buffer[100];
		char response[100];
		error=recv(clientsock,buffer,100,0);
		if(error==-1){
			printf("error in recving\n");
		}
		printf("client:%s",buffer);
		memset(buffer,0,100);
		printf("server:");
		fgets(response,100,stdin);
		send(clientsock,response,100,0);
		if(strncmp(response,"exit",4)==0){
			i=0;
		}
	}
	close(serversock);
	close(clientsock);
}
