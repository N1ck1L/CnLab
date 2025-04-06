#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
	int clientsock,error;
	struct sockaddr_in client;
	
	clientsock=socket(AF_INET,SOCK_DGRAM,0);
	
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=htons(3004);
	char buffer[100];
	printf("enter the message:");
	scanf("%s",buffer);
	socklen_t len=sizeof(client);
	error=sendto(clientsock,buffer,100,0,(struct sockaddr*)&client,len);
	if(error==-1){
		printf("sending error\n");
	}
	memset(buffer,0,100);
	
	error=recvfrom(clientsock,buffer,100,0,(struct sockaddr*)&client,&len);
	if(error==-1){
		printf("receiving error\n");
	}
	
	printf("time:%s",buffer);
	close(clientsock);

}
