#include<stdio.h>
#include<stdlib.h>


int node;
int cost[10][10],dis[10][10],nexthop[10][10];

void main(){
    printf("enter the number of node:");
    scanf("%d",&node);

    printf("enter the cost matrix(no connection 9999\n)");

    for(int i=0;i<node;i++){
        for(int j=0;j<node;j++){
            scanf("%d",&cost[i][j]);
            if(i==j){
                cost[i][j]=0;
            }
            dis[i][j]=cost[i][j];
            nexthop[i][j]=j;
        }
    }

    int update;
    do{
        update=0;
        for(int i=0;i<node;i++){
            for(int j=0;j<node;j++){
                for(int k=0;k<node;k++){
                    if(dis[i][j]>dis[i][k]+dis[k][j]){
                        dis[i][j]=dis[i][k]+dis[k][j];
                        nexthop[i][j]=nexthop[i][k];
                        update=1;
                    }
                }
            }
        }

    }while(update);

    for(int i=0;i<node;i++){
        printf("routing table of %d router\n",i+1);
        printf("router\tdistance\tnextnode\n");
        for(int j=0;j<node;j++){
            printf("%d\t%d\t%d\n",j+1,dis[i][j],nexthop[i][j]+1);
        }
    }



}