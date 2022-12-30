#include "memoryhdr.h"

void ascSort(int *arr,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<n;j++)
		{
			if(arr[i]>arr[j])
			{
				int temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
void descSort(int *arr,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<n;j++)
		{
			if(arr[i]<arr[j])
			{
				int temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
int firstFit(int nm,int *memory,int np,int *process)
{
 	int count=0,fragment=0,exFragment=0;
	int *hole=(int*)malloc(nm*sizeof(int));
 	for(int i=0;i<np;i++)
  		hole[i]=0;
 	for(int i=0;i<np;i++)
	{
  		count=0;
		for(int j=0;j<nm;j++)
		{
			count+=1;
			if(hole[j]==0)
			{
				if(process[i]<=memory[j])
				{
					printf("\nProcess P%d Size: %d Memory: %d ",i,process[i],memory[j]);
					hole[j]=1;
					fragment+=memory[j]-process[i];
					break;
				}
			}
		}
		if(count==nm && hole[nm-1]==0)
			printf("\nProcess P%d with size %d cannot fit in memory",i,process[i]);
 	}
 	for(int i=0;i<nm;i++)
	{
		if(hole[i]==0)
			exFragment+=memory[i];
 	}
	printf("\nFirst Fit");
	printf("\nThe Internal Fragmentation is %d\n",fragment);
	printf("The External Fragmentation is %d\n",exFragment+fragment);
 	return fragment+exFragment;
}

int bestFit(int nm,int *memory,int np,int *process)
{
 	int bestFitHole=-1,fragment=0,exFragment=0;
	int *hole=(int*)malloc(nm*sizeof(int));
 	for(int i=0;i<np;i++)
  		hole[i]=0;
	int memcpy[nm];
	for(int i=0;i<nm;i++)
		memcpy[i]=memory[i];
	ascSort(memcpy,nm);
 	for(int i=0;i<np;i++)
	{
  		bestFitHole=-1;
  		for(int j=0;j<nm;j++)
		{
			if(hole[j]==0)
			{
				if(process[i]<=memcpy[j])
				{
					if(bestFitHole==-1)
						bestFitHole=j;
					else if(memcpy[j]<memcpy[bestFitHole])
						bestFitHole=j;
				}
			}
  		}
  		if(bestFitHole!=-1)
		{
			printf("\nProcess P%d Size: %d Memory: %d ",i,process[i],memcpy[bestFitHole]);
			hole[bestFitHole]=1;
			fragment+=memcpy[bestFitHole]-process[i];
		}
		else
			printf("\nProcess P%d with size %d cannot fit in memory",i,process[i]);
 	}
	for(int i=0;i<nm;i++)
	{
		if(hole[i]==0)
			exFragment+=memcpy[i];
	}
	printf("\nBest Fit");
	printf("\nThe Internal Fragmentation is %d\n",fragment);
	printf("The External Fragmentation is %d\n",exFragment+fragment);
	return fragment+exFragment;
}

int worstFit(int nm,int *memory,int np,int *process)
{
 	int worstFitHole=-1,fragment=0,exFragment=0;
	int *hole=(int*)malloc(nm*sizeof(int));
 	for(int i=0;i<np;i++)
  		hole[i]=0;
	int memcpy[nm];
	for(int i=0;i<nm;i++)
		memcpy[i]=memory[i];
	descSort(memcpy,nm);
 	for(int i=0;i<np;i++)
	{
  		worstFitHole=-1;
		for(int j=0;j<nm;j++)
		{
			if(hole[j]==0)
			{
				if(process[i]<=memcpy[j])
				{
					if(worstFitHole==-1)
						worstFitHole=j;
					else if(memcpy[j]>memcpy[worstFitHole])
						worstFitHole=j;
				}
   			}
  		}
		if(worstFitHole!=-1)
		{
			printf("\nProcess P%d Size: %d Memory: %d ",i,process[i],memcpy[worstFitHole]);
			hole[worstFitHole]=1;
			fragment+=memcpy[worstFitHole]-process[i];
		}
		else
			printf("\nProcess P%d with size %d cannot fit in memory",i,process[i]);
	}
	for(int i=0;i<nm;i++)
	{
		if(hole[i]==0)
			exFragment+=memcpy[i];
	}
	printf("\nWorst Fit");
	printf("\nThe Internal Fragmentation is %d\n",fragment);
	printf("The External Fragmentation is %d\n",exFragment+fragment);
	return fragment+exFragment;
}

void optimumFit(int nm,int *memory,int np,int *process)
{
 	int arr[3]; 
	arr[0]=firstFit(nm,memory,np,process);
	arr[1]=bestFit(nm,memory,np,process);
	arr[2]=worstFit(nm,memory,np,process);
	int index=0;
	for(int j=1;j<3;j++)
	{
		if(arr[index]>=arr[j])
		index=j;
	}
	if(index==0)
		printf("\nFirst fit is optimum");
	else if(index==1)
		printf("\nBest fit is optimum");
	else
		printf("\nWorst fit is optimum");
}