#include "deadlockhdr.h"

int main()
{
	int n,m,ch;
	struct deadlock *d=(struct deadlock*)malloc(sizeof(struct deadlock));
	
	printf("Enter the number of process: ");
	scanf("%d",&n);
	printf("Enter the number of resources: ");
	scanf("%d",&m);

 	d->available=(int*)malloc(m*sizeof(int ));

	printf("Enter the Available Vector: ");
	for(int i=0;i<m;i++)
  		scanf("%d",&d->available[i]);

	printf("\nMax Matrix\n");
	d->max=(int**)malloc(n*sizeof(int *));
 	for(int i=0;i<n;i++)
  		d->max[i]=(int *)malloc(m*sizeof(int));
 	for(int i=0;i<n;i++)
	{
  		printf("Enter max resource for process P%d: ",i);
  		for(int j=0;j<m;j++)
   			scanf("%d",&d->max[i][j]);
 	}
	printf("\nAllocaion Matrix\n");
	d->allocation=(int **)malloc(n*sizeof(int*));
 	for(int i=0;i<n;i++)
  		d->allocation[i]=(int *)malloc(m*sizeof(int));
 	for(int i=0;i<n;i++)
	{
  		printf("Enter allocated resources for process P%d: ",i);
  		for(int j=0;j<m;j++)
   			scanf("%d",&d->allocation[i][j]);
 	}
 	//find need
 	d->need=(int**)malloc(n*sizeof(int*));
 	for(int i=0;i<n;i++)
  		d->need[i]=(int*)malloc(m*sizeof(int));
 	for(int i=0;i<n;i++)
  		for(int j=0;j<m;j++)
   			d->need[i][j]=d->max[i][j]-d->allocation[i][j];
 	do
 	{
		printf("\n==========================MENU==========================\n");
		printf("1 -> Safe State\n");
		printf("2 -> Request Resource\n");
		printf("3 -> Display Allocaion, Max, Available, Need Details\n");
		printf("4 -> Exit\n");
		printf("========================================================\n\n");
		printf("Enter your choice: ");
  		scanf("%d",&ch);
  		switch(ch)
		{
			case 1:
				int res = safetyAlgorithm(d,n,m);
				if(res==1)
					printf("\nThe system is in safe state\n");
				else
					printf("\nThe system is not in safe state\n");
				break;
   			case 2:
				int p;
				int *req =(int*)malloc(m*sizeof(int));
				printf("Enter process to request: ");
				scanf("%d",&p);
				printf("Enter resources to request: ");
				for(int i=0;i<m;i++)
					scanf("%d",&req[i]);
				res = resourceRequest(d,n,m,p,req);
				if(res==1)
					printf("\nThe request is accepted\n");
				else
					printf("\nThe request is not accepted\n");
				break;
			case 3:
				display(d,n,m);
				break;
			case 4:
				break;
			default:
				printf("Enter a valid choice\n");
  		}
 	}while(ch!=4);
}
