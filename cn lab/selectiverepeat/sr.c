 #include<stdio.h>
 #include<stdlib.h>
 
 struct node{
 	int packet;
 	struct node*next;
 };
 
 struct node*head=NULL;
 struct node*headre=NULL;
 
 void addnode(int pack,int retran){
	struct node*temp;
 	struct node*newnode=(struct node*)malloc(sizeof(struct node));
 	if(retran==0){
 		temp=head;
 	}
 	else{
		temp=headre;
	}
	newnode->packet=pack;
	if(temp==NULL){
		if(retran==0){
			head=newnode;
			newnode->next=NULL;
			temp=head;
		}
		else{
			headre=newnode;
			newnode->next=NULL;
			temp=headre;			
		}	
	}
	else{
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=newnode;
		newnode->next=NULL;
		
	}
 	
 }
 
 void main(){
 	int n,size;
 	printf("enter the number of frames:");
 	scanf("%d",&n);
 	printf("enter the size of sliding window");
 	scanf("%d",&size);
 	
 	int i;
 	for(i=0;i<size;i++){
 		addnode(i,0);
 	}
 	
 	
 	while(head!=NULL){
 		printf("packet%d send\n",head->packet);
 		int lost=rand()%n;
 		if(lost==head->packet){
 			printf("packet%d acknowledgement not received\n",head->packet);
 			addnode(head->packet,1);
 			head=head->next;
 		}
 		else{
 			printf("packet%d acknowledgement received\n",head->packet);
 			if(headre==NULL){
				if(i<n){
 					addnode(i,0);
 					i++;
				}
 			}
 			struct node*temp=head;
 			head=head->next;
 			free(temp);
 		}
 		
 		if(head==NULL){
 			while(headre!=NULL){
 				printf("packet%d retransmitting\n",headre->packet);
 				int lost=rand()%n;
 				if(lost==headre->packet){
 					printf("packet%d acknowledgement not received\n",headre->packet);
 					addnode(headre->packet,1);
 					headre=headre->next;	
 				}
 				else{
 					printf("packet%d acknowledgement received\n",headre->packet);
 					struct node*temp2=headre;
 					headre=headre->next;
 					free(temp2);
 				}
 			}
 			if(i<n){
 				addnode(i,0);
 				i++;
 			}
 		
 		}

 	}
 
 
 }
