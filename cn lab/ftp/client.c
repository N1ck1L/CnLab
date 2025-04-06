#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void main(){
	int error,clientsock;
	struct sockaddr_in client;
	
	clientsock=socket(AF_INET,SOCK_STREAM,0);
	
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=htons(8080);
	
	error=connect(clientsock,(struct sockaddr*)&client,sizeof(client));
	if(error==-1){
		printf("error in connecting\n");
	}
	
	char buffer[100];
	printf("enter the name of file:\n");
	scanf("%s",buffer);
	
	error=send(clientsock,buffer,100,0);
	if(error==-1){
		printf("error in sending\n");
	}
	char content[100];
	char pid[100];
	error=recv(clientsock,pid,100,0);
	printf("%s\n",pid);
	error=recv(clientsock,content,100,0);
	if(error==-1){
		printf("error in recv\n");
	}
	else{
		printf("%s\n",content);
	}
	memset(content,0,100);
	close(clientsock);
}
