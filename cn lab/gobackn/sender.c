#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node{
    int packet;
    struct node* next;
};

struct node* head = NULL;


void addnode(int pack){
	struct node*newnode=(struct node*)malloc(sizeof(struct node));
    struct node*temp= head;
	newnode->packet=pack;
	if(head==NULL){
		head=newnode;
		newnode->next=NULL;
		temp=newnode;
	}
    else{
        while(temp -> next != NULL)
            temp = temp -> next;
        temp -> next = newnode;
        temp=newnode;
    }
		
		
}



void main(){
	int sendersock,error;
	struct sockaddr_in sender;
	sendersock=socket(AF_INET,SOCK_STREAM,0);
	
	struct timeval timer;
	printf("enter the timer:");
	scanf("%ld",&timer.tv_sec);
	timer.tv_usec=0;
	
	error=setsockopt(sendersock,SOL_SOCKET,SO_RCVTIMEO,&timer,sizeof(timer));
	if(error==-1){
		printf("socket setup failed\n");
	}
	
	sender.sin_family=AF_INET;
	sender.sin_addr.s_addr=inet_addr("127.0.0.1");
	sender.sin_port=htons(8100);
	
	error=connect(sendersock,(struct sockaddr*)&sender,sizeof(sender));
	if(error==-1){
		printf("connection error\n");
	}
	
	int n,size;
	printf("enter the number of frames:");
	scanf("%d",&n);
	
	printf("enter the size of sliding window");
	scanf("%d",&size);
	
	int i=0;
	for(i=0;i<size;i++){
		addnode(i);
	}
	
	while(head != NULL){
		struct node* temp1= head;
		char buffer[100];
		sprintf(buffer,"%d",temp1->packet);
		error=send(sendersock,buffer,100,0);
		if(error == -1){
			printf("sending error");
		}
		printf("packet %d has been send to receiver\n",temp1->packet);
		memset(buffer,100,0);
		
		error=recv(sendersock,buffer,100,0);
		if(error == -1){
			struct node*temp2=temp1->next;
			while(temp2->next!= NULL){
				printf("packet %d has been send to receiver\n",temp2->packet);
				temp2=temp2->next;
			}
			printf("retransmitting packet %d\n",temp1->packet);
			sleep(1);
		}
		else{
			printf("acknoledgment for packet %s received\n",buffer);
        }
		if(i<n){
			addnode(i);
		}
		head=head->next;
		free(temp1);
		i++;
		
		
	
	}
	
	close(sendersock);

}
