#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

void main(){

    int sendersock,error;
    struct sockaddr_in sender;
    sendersock=socket(AF_INET,SOCK_STREAM,0);

    struct timeval timer;
    printf("enter timer");
    scanf("%ld", &timer.tv_sec);
    timer.tv_usec=0;
    error=setsockopt(sendersock,SOL_SOCKET,SO_RCVTIMEO,&timer,sizeof(timer));
    if(error == -1){
        printf("socket setup failed\n");
    }
    sender.sin_family=AF_INET;
    sender.sin_addr.s_addr=inet_addr("127.0.0.1");
    sender.sin_port=htons(8100);
    error=connect(sendersock,(struct sockaddr*)&sender,sizeof(sender));
    if(error==-1){
        printf("connection failed\n");
    }
    printf("enter the number of frames:");
    int n;
    scanf("%d",&n);
    int i=0;

    while(i<n){
        char buffer[100];
        sprintf(buffer,"%d",i);
        error=send(sendersock,buffer,100,0);
        if(error==-1){
            printf("error in sending message\n");
        }
        printf("packet %d hs been sent\n",i);
        memset(buffer,0,100);
        error=recv(sendersock,buffer,100,0);
        if(error==-1){
            printf("packet %d lost\n",i);
            sleep(1);
            printf("retransmitting packet %d\n",i);
        }
        else{
            printf("acknowledgement for %s has been received\n",buffer);
        i++;
        }
    }
    close(sendersock);
}

