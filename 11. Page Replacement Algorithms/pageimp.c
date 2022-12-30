#include "pagehdr.h"

int FIFO(int refsize,int *reflist,int framesize)
{
	int index,pageFault=0;
 	int *page=(int*)malloc(framesize*sizeof(int));
 	int *time=(int*)malloc(framesize*sizeof(int));
 	for(int i=0;i<framesize;i++)
	{
		page[i]=-1;
		time[i]=i;
 	}
 	printf("\nPage\n");
 	for(int i=0;i<refsize;i++)
 	{
  		index=-1;
  		for(int j=0;j<framesize;j++)
		{
			if(reflist[i]==page[j])
			{
				index=i;
				break;
			}
		}
		if(index==-1)
		{
			// if page not present
			pageFault+=1;
			index=0;
			for(int k=0;k<framesize;k++)
			{
				if(page[k]==-1)
				{ 
					//frame is available
					index=k;
					break;
				}
				if(time[index]>time[k]) //check reference for less time
					index=k;
			}
			page[index]=reflist[i];
			time[index]=framesize-1; //make new reference in memory with more time
			for(int j=0;j<framesize;j++)
			{ 
				//decrement all reference except current one
				if(index!=j)
					time[j]-=1;
			}
		}
		printf("\n%d ",reflist[i]);
		for(int j=0;j<framesize;j++)
			printf("%d ",page[j]);
 	}
	printf("\n\nNumber of page faults = %d\n",pageFault);
	return pageFault;
}

int LRU(int refsize,int *reflist,int framesize)
{
 	int index,index1,pageFault=0;
 	int *page=(int*)malloc(framesize*sizeof(int));
 	int *time=(int*)malloc(framesize*sizeof(int));
 	for(int i=0;i<framesize;i++)
	{
		//initialize page and time
		page[i]=0;
		time[i]=i;
 	}
 	printf("\nPage\n");
 	for(int i=0;i<refsize;i++)
	{
  		index1=-1;
  		for(int j=0;j<framesize;j++)
		{
			//check reference in memory page
   			if(reflist[i]==page[j])
			{
				index1=j;
				break;
   			}
  		}
  		if(index1==-1)
		{
			// if reference not present
			pageFault+=1;
			index=0;
   			for(int k=0;k<framesize;k++)
			{
    			if(page[k]==0)
				{
					//if memory page is empty
					index=k;
					break;
				}
				if(time[index]>time[k])//check reference for less time
					index=k;
   			}
			page[index]=reflist[i];
			time[index]=framesize-1;//make new reference in memory with more time
			for(int j=0;j<framesize;j++)
			{
				//decrement all reference except current one
				if(index!=j)
					time[j]-=1;
			}
  		}
		else
		{
			if(reflist[i]!=reflist[i-1])
			{
				time[index1]=framesize-1;
				for(int j=0;j<framesize;j++)
				{
					if(index1!=j)
						time[j]-=1;
				}
			}
		}
		printf("\n%d ",reflist[i]);
		for(int j=0;j<framesize;j++)
			printf("%d ",page[j]);
 	}
	printf("\n\nNumber of page faults = %d\n",pageFault);
	return pageFault;
}
int OPTIMAL(int refsize,int *reflist,int framesize)
{
 	int index,index1,pageFault=0,count=0;
 	int *page=(int*)malloc(framesize*sizeof(int));
 	int *time=(int*)malloc(framesize*sizeof(int));
 	for(int i=0;i<framesize;i++)
	{
		//initialize page and time
		page[i]=0;
		time[i]=refsize;
 	}
 	printf("\nPage\n");
 	for(int i=0;i<refsize;i++)
	{
  		index1=-1;
  		for(int j=0;j<framesize;j++)
		{
			//check reference in memory page
   			if(reflist[i]==page[j])
			{
				index1=j;
				break;
   			}
  		}
  		if(index1==-1)
		{
			// if reference not present
			pageFault+=1;
			index=0;
			for(int k=0;k<framesize;k++)
			{
				if(page[k]==0)
				{
					//if memory page is empty
					index=k;
					break;
				}
				if(time[index]<time[k])//check reference for more time
					index=k;
			}
			page[index]=reflist[i];
			count=0;
			for(int j=i+1;j<refsize;j++)
			{
				if(reflist[i]==reflist[j])
				{
					//if reference is in list
					time[index]=j;
					count=1;
					break;
				}
			}
  			if(count==0) //if reference not in list
   				time[index]=refsize;
  		}
  		else
		{
   			count=0;
   			for(int j=i+1;j<refsize;j++)
			{
    			if(reflist[i]==reflist[j])
				{
					time[index1]=j;
					count=1;
					break;
				}
   			}
			if(count==0)
				time[index1]=refsize;
  		}
		printf("\n%d ",reflist[i]);
		for(int j=0;j<framesize;j++)
			printf("%d ",page[j]);
 	}
 	printf("\n\nNumber of page faults = %d\n",pageFault);
 	return pageFault;
}
void BEST(int refsize,int *reflist,int framesize)
{
	int arr[3];
	arr[0]=FIFO(refsize,reflist,framesize);
	arr[1]=LRU(refsize,reflist,framesize);
	arr[2]=OPTIMAL(refsize,reflist,framesize);
	int index=0;
 	for(int j=1;j<3;j++)
  		if(arr[index]>arr[j])
  	 		index=j;
 	if(index==0)
  		printf("FIFO Algorithm is best for the sequence.\n");
	else if(index==1)
  		printf("LRU Algorithm is best for the sequence.\n");
 	else
  		printf("OPTIMAL Algorithm is best for the sequence.\n");
}