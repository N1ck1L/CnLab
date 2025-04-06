#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>

void main(){
	
	int serversock,clientsock,error;
	struct sockaddr_in server,client;
	
	serversock=socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(8080);
	
	error=bind(serversock,(struct sockaddr*)&server,sizeof(server));
	if(error==-1){
		printf("error in binding\n");
	}
	
	error=listen(serversock,1);
	if(error==-1){
		printf("error in listening\n");
	}
	socklen_t len =sizeof(client);
	clientsock=accept(serversock,(struct sockaddr*)&client,&len);
	if(clientsock==-1){
		printf("error in accpeting\n");
	}
	
	char filename[100];
	char buffer[100];
	char proid[100];
	error=recv(clientsock,filename,100,0);
	if(error==-1){
		printf("error in recving\n");
	}

	sprintf(proid,"%d",getpid());
	send(clientsock,proid,strlen(proid),0);
	
	FILE *file =fopen(filename,"r");
	
	while(fgets(buffer,100,file)!=NULL){
		error=send(clientsock,buffer,strlen(buffer),0);
		if(error==-1){
			printf("error in sending\n");
		}
		memset(buffer,0,100);
	}
	fclose(file);
	close(serversock);
	close(clientsock);
	
	
	

}

