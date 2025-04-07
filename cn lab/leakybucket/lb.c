#include<stdio.h>
#include<stdlib.h>

void main(){
	int bucketcap,leakrate,n;
	
	printf("bucketcap:");
	scanf("%d",&bucketcap);
	printf("leakrate:");
	scanf("%d",&leakrate);
	printf("enter the no. of packets:");
	scanf("%d",&n);
	int packet[n];
	printf("packets:");
	for(int i=0;i<n;i++){
		scanf("%d",&packet[i]);
	}
	
	int time=1;
	int inbucket;
	printf("time\tpno\tpsize\tinbucket\tdroped\t\tinbucket(after leakage)\n");
	for(int i=0;i<n;i++){
		int droped=0,leaked=0;
		inbucket+=packet[i];
		if(inbucket>bucketcap){
			droped=inbucket-bucketcap;
			inbucket=bucketcap;
		}
		
		if(leakrate<inbucket){
			leaked=leakrate;
		}
		else{
			leaked=inbucket;
		}
		
		printf("%d\t%d\t%d\t%d\t\t%d\t\t",time,i+1,packet[i],inbucket,droped);
		inbucket=inbucket-leaked;
		printf("%d\n",inbucket);
		time++;
	}
	
	while(inbucket>0){
		int leaked=0;
		if(leakrate<=inbucket)
			leaked=leakrate;
		else
			leaked=inbucket;
		printf("%d\t-\t-\t%d\t\t-\t\t",time,inbucket);
		inbucket=inbucket-leaked;
		printf("%d\n",inbucket);
		time++;
	}
}
