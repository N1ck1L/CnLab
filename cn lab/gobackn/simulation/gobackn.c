#include<stdio.h>
#include<stdlib.h>

struct node{
	int packet;
	struct node*next;	
};

struct node* head=NULL;

void addnode(int pack){
	struct node*temp=head;
	struct node*newnode=(struct node*)malloc(sizeof(struct node));
	newnode->packet=pack;
	
	if(head==NULL){
		head=newnode;
		newnode->next=NULL;
		temp=head;
	}
	else{
		while(temp->next!= NULL){
			temp=temp->next;
		}
		temp->next=newnode;
		newnode->next=NULL;
	}
}

void main(){

	int n,timer,size;
	printf("enter the number of frames:");
	scanf("%d",&n);
	printf("timer:");
	scanf("%d",&timer);
	printf("size of sliding window:");
	scanf("%d",&size);
	int i;
	for(i=0;i<size;i++){
		addnode(i);
	}
	
	while(head!=NULL){
		printf("the packet %d is send\n",head->packet);
		int lost=rand()%n;
		if(head->packet==lost){
			printf("acknowledgment of packet%d not received\n",head->packet);
			struct node*temp=head->next;
			while(temp != NULL){
				printf("the packet %d is send\n",temp->packet);
				printf("the packet %d is discarded\n",temp->packet);
				temp=temp->next;
			}
			printf("the packet %d is retransmitting\n",head->packet);
		}
		else{
			printf("acknowledgment of packet%d received\n",head->packet);
			struct node*temp=head;
			head=head->next;
			free(temp);
			if(i<n){
				addnode(i);
				i++;
			}
		
		}
	
	}

}
