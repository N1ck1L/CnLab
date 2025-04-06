#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>


void main(){
    int sendersock,receiversock,error;
    struct sockaddr_in sender,receiver;

    receiversock=socket(AF_INET,SOCK_STREAM,0);

    receiver.sin_family=AF_INET;
    receiver.sin_addr.s_addr=inet_addr("127.0.0.1");
    receiver.sin_port=htons(8100);

    error=bind(receiversock,(struct sockaddr*)&receiver,sizeof(receiver));
    if(error == -1){
        printf("error in binding\n");
    }

    error=listen(receiversock,1);
    if(error == -1){
        printf("error in listening");
    }
    
    socklen_t len = sizeof(sender);
    sendersock=accept(receiversock,(struct sockaddr*)&sender,&len);
    while(1){
        char buffer[100];
        error=recv(sendersock,buffer,100,0);
        printf("received packet %s from sender\n",buffer);
        error=send(sendersock,buffer,100,0);
        if(error==-1){
            printf("error in sending\n");
        }
        printf("ackonwledgmentfor packet %s send\n",buffer);
    }
    close(receiversock);
    close(sendersock);

}