#include "deadlockhdr.h"

int safetyAlgorithm(struct deadlock *d,int n,int m)
{
	int *work=(int*)malloc(m*sizeof(int));
	bool *finish=(bool*)malloc(n*sizeof(bool));
	bool *prev_finish=(bool*)malloc(n*sizeof(bool));
	int count;

	for(int i=0;i<m;i++)
  		work[i]=d->available[i];

	for(int i=0;i<n;i++)
		finish[i]=false;

	for(int i=0;i<n;i++)
		prev_finish[i]=false;

 	printf("\nSafe Sequence: ");
 	while(1)
	{
  		for(int i=0;i<n;i++)
		{
   			if(finish[i]==false)
			{
				count=0;
				for(int j=0;j<m;j++)
				{
					if(d->need[i][j]<=work[j])
					count+=1;
				}
    			if(count==m)
				{ 
					//if need<=work
					printf("\nP%d\t",i);
					finish[i]=true;
					printf("\nwork\t");
					for(int j=0;j<m;j++)
					{
						work[j]+=d->allocation[i][j];
						printf("%d ",work[j]);
     				}
    			}
   			}
  		}
  		count=0;
  		for(int i=0;i<n;i++)
		{ 
			// check any change in finish
   			if(finish[i]==prev_finish[i])
   	 			count+=1;
   			prev_finish[i]=finish[i];
  		}
  		if(count==n)
   			break;
 	}
 	for(int i=0;i<n;i++)
	{
  		if(finish[i]==false)
   			return -1;
 	}
 	return 1;
}

int resourceRequest(struct deadlock *d,int n,int m,int p, int *request)
{
	for(int i=0;i<m;i++)
	{ 
		//check request<=need
		if(request[i]>d->need[p][i])
			return -1;
 	}
	for(int i=0;i<m;i++)
	{ 
		//check request<=available
		if(request[i]>d->available[i])
			return -1;
	}
 	for(int i=0;i<m;i++)
	{
		d->available[i]-=request[i];
		d->allocation[p][i]+=request[i];
		d->need[p][i]-=request[i];
 	}
 	int res = safetyAlgorithm(d,n,m);
 	for(int i=0;i<m;i++)
	{
		d->available[i]+=request[i];
		d->allocation[p][i]-=request[i];
		d->need[p][i]+=request[i];
 	}
	if(res==1)
		return 1;
	else
		return -1;
}

void display(struct deadlock *d,int n,int m)
{
 	printf("\nAllocation Matrix\n");
 	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			printf("%d\t",d->allocation[i][j]);
		printf("\n");
 	}
 	printf("\nMax Matrix\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			printf("%d\t",d->max[i][j]);
		printf("\n");
	}
	printf("\nNeed Matrix\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			printf("%d\t",d->need[i][j]);
		printf("\n");
	}
 	printf("\nAvailable Vector: ");
 	for(int i=0;i<m;i++)
  		printf("%d\t",d->available[i]);
}
