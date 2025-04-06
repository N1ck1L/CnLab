#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void main(){
	int serversock,error;
	struct sockaddr_in server,client;
	
	serversock=socket(AF_INET,SOCK_DGRAM,0);
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(3004);
	
	error=bind(serversock,(struct sockaddr*)&server,sizeof(server));
	if(error==-1){
		printf("binding error\n");
	}
	char buffer[100];
	socklen_t len = sizeof(client);
	error=recvfrom(serversock,buffer,100,0,(struct sockaddr*)&client,&len);
	if(error==-1){
		printf("recving error\n");
	}
	char timer[1000];
	if(strcmp(buffer,"time")==0){
		struct tm* now;
		time_t currenttime = time(NULL);
		now=localtime(&currenttime);
		strftime(timer,1000,"%D %H:%M:%S",now);
		//sprintf(timer,"%ld",currenttime);
		error=sendto(serversock,timer,1000,0,(struct sockaddr*)&client,len);
	}
	close(serversock);
	

}
