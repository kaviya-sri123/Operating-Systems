#include "diskhdr.h"

int absdiff(int a,int b)
{
	if(a>=b)
		return a-b;
	return b-a;
}
int* sort(int *arr,int n)
{
 	for(int i=0;i<n-1;i++)
	{
  		for(int j=i+1;j<n;j++)
		{
   			if(arr[i]>arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
   			}
  		}
 	}
 	return arr;
}
void FCFS(int ncyl,int nreq,int *reqorder,int headpos)
{
	printf("\nFCFS");
	int seekTime = 0;
 	printf("\nRequest Order: ");
 	for(int i=0;i<nreq;i++)
  		printf("%d ",reqorder[i]);
 	for(int i=0;i<nreq;i++)
	{
  		seekTime = seekTime + absdiff(reqorder[i],headpos);
  		printf("\n%d - %d = %d",headpos,reqorder[i],absdiff(reqorder[i],headpos));
  		headpos = reqorder[i];
 	}
 	printf("\nSeek Time = %d",seekTime);
}

void SSTF(int ncyl,int nreq,int *reqorder,int headpos)
{
	printf("\nSSTF");
	int seekTime = 0,flag[nreq];
	for(int i=0;i<nreq;i++)
  		flag[i]=0;
 	int temp = headpos,temp1,mincy = 0,mindiff = ncyl;
	printf("\nRequest Order: ");
 	for(int i=0;i<nreq;i++)
  		printf("%d ",reqorder[i]);
 	for(int i=0;i<nreq;i++)
 	{ 
		//find seek time
  		mindiff = ncyl;
  		for(int j=0;j<nreq;j++)
		{ 
			//find less distance from head
   			if(flag[j]==0)
			{
    			temp1 = absdiff(reqorder[j],headpos);
    			if(mindiff>temp1)
				{
					mindiff=temp1;
					mincy=j;
				}
   			}
  		}
		flag[mincy]=1;
		seekTime = seekTime + mindiff;
		printf("\n%d - %d = %d",headpos,reqorder[mincy],mindiff);
		headpos = reqorder[mincy];
 	}
 	printf("\nSeek Time = %d",seekTime);
}

void SCAN(int ncyl,int nreq,int *reqorder,int headpos,int prevheadpos)
{
 	printf("\nSCAN");
 	int seekTime = 0,i,mincy,maxcy,indexR;
	int *reqorder1 = (int*)malloc(nreq*sizeof(int));
	for(int i=0;i<nreq;i++)
		reqorder1[i]=reqorder[i];
 	reqorder1 = sort(reqorder1,nreq);
 	printf("\nRequest order (After Sorting): ");
 	for(i=0;i<nreq;i++)
  		printf("%d ",reqorder1[i]);
 	mincy = reqorder1[0];
 	maxcy = reqorder1[nreq-1];
	for(i = 0;i<nreq;i++)
	{
		if(reqorder1[i]>headpos)
			break;
	}
 	indexR=i;
 	if(headpos - prevheadpos > 0)
 	{
  		seekTime = seekTime + absdiff(headpos,(ncyl-1));
  		printf("\n%d - %d = %d",headpos,(ncyl-1),absdiff(headpos,(ncyl-1)));
  		seekTime = seekTime + absdiff(mincy,(ncyl-1));
  		printf("\n%d - %d = %d",mincy,(ncyl-1),absdiff(mincy,(ncyl-1)));
 	}
	else
	{
		seekTime = seekTime + headpos;
		printf("\n%d - %d = %d",headpos,0,headpos);
		seekTime = seekTime + maxcy;
		printf("\n%d - %d = %d",maxcy,0,maxcy);
	}
 	printf("\nSeek Time = %d",seekTime);
}

void CSCAN(int ncyl,int nreq,int *reqorder,int headpos, int prevheadpos)
{
 	printf("\nCSCAN");
 	int seekTime = 0,i,mincy,maxcy,indexR;
	int *reqorder1 = (int*)malloc(nreq*sizeof(int));
	for(int i=0;i<nreq;i++)
		reqorder1[i]=reqorder[i];
 	reqorder1 = sort(reqorder1,nreq);
 	printf("\nRequest order (After sorting): ");
 	for(i=0;i<nreq;i++)
  		printf("%d ",reqorder1[i]);
	mincy = reqorder1[0];
	maxcy = reqorder1[nreq-1];
 	for(i = 0;i<nreq;i++)
	{
		if(reqorder1[i]>headpos)
			break;
	}
 	indexR=i;
 	if(headpos - prevheadpos > 0)
	{
		seekTime = seekTime + absdiff(headpos,(ncyl-1));
		printf("\n%d - %d = %d",headpos,(ncyl-1),absdiff(headpos,(ncyl-1)));
		seekTime = seekTime + ncyl-1;
		printf("\n%d - %d = %d",(ncyl-1),0,(ncyl-1));
		seekTime = seekTime + reqorder1[indexR-1];
		printf("\n%d - %d = %d",reqorder1[indexR-1],0,reqorder1[indexR-1]);
 	}
 	else
	{
  		seekTime = seekTime + headpos+ ncyl-1;
  		seekTime = seekTime + absdiff(reqorder1[i],199);
  		seekTime = seekTime + headpos;
  		printf("\n%d - %d = %d",headpos,0,headpos);
  		seekTime = seekTime + ncyl-1;
  		printf("\n%d - %d = %d",(ncyl-1),0,(ncyl-1));
  		seekTime = seekTime + absdiff(reqorder[indexR],(ncyl-1));
  		printf("\n%d - %d = %d",reqorder[indexR],(ncyl-1),absdiff(reqorder[indexR-1],ncyl-1));
	}
	printf("\nSeek Time = %d",seekTime);
}

void LOOK(int ncyl,int nreq,int *reqorder,int headpos, int prevheadpos)
{
 	printf("\nLOOK");
 	int seekTime = 0,mincy,maxcy,i;
	int *reqorder1 = (int*)malloc(nreq*sizeof(int));
	for(int i=0;i<nreq;i++)
		reqorder1[i]=reqorder[i];
 	reqorder1 = sort(reqorder,nreq);
	printf("\nRequest order (After sorting): ");
 	for(i=0;i<nreq;i++)
  		printf("%d ",reqorder1[i]);
	mincy = reqorder1[0];
	maxcy = reqorder1[nreq-1];
	if(headpos - prevheadpos > 0)
	{
		seekTime = seekTime + absdiff(headpos,maxcy);
		printf("\n%d - %d = %d",headpos,maxcy,absdiff(headpos,maxcy));
		seekTime = seekTime + absdiff(mincy,maxcy);
		printf("\n%d - %d = %d",mincy,maxcy,absdiff(mincy,maxcy));
	}
 	else
 	{
  		seekTime = seekTime + absdiff(headpos,mincy);
  		printf("\n%d - %d = %d",headpos,mincy,absdiff(headpos,mincy));
  		seekTime = seekTime + absdiff(mincy,maxcy);
  		printf("\n%d - %d = %d",mincy,maxcy,absdiff(mincy,maxcy));
 	}
 	printf("\nSeek Time = %d",seekTime);
}

void CLOOK(int ncyl,int nreq,int *reqorder,int headpos,int prevheadpos)
{
 	printf("\nCLOOK");
 	int seekTime = 0,i,mincy,maxcy,indexR;
 	int *reqorder1 = (int*)malloc(nreq*sizeof(int));
	for(int i=0;i<nreq;i++)
		reqorder1[i]=reqorder[i];
 	reqorder1 = sort(reqorder,nreq);
	printf("\nRequest order (After sorting): ");
 	for(i=0;i<nreq;i++)
  		printf("%d ",reqorder1[i]);
 	mincy = reqorder1[0];
 	maxcy = reqorder1[nreq-1];
 	for(i = 0;i<nreq;i++)
  		if(reqorder1[i]>headpos)
   			break;
 	indexR=i;
 	if(headpos - prevheadpos > 0)
	{
		seekTime = seekTime + absdiff(headpos,maxcy);
		printf("\n%d - %d = %d",headpos,maxcy,absdiff(headpos,maxcy));
		seekTime = seekTime + absdiff(maxcy,mincy);
		printf("\n%d - %d = %d",mincy,maxcy,absdiff(mincy,maxcy));
		seekTime = seekTime + absdiff(reqorder1[indexR-1],mincy);
		printf("\n%d - %d = %d",mincy,reqorder1[indexR-1],absdiff(mincy,reqorder1[indexR-1]));
	}
 	else
	{
		seekTime = seekTime + absdiff(headpos,mincy);
		printf("\n%d - %d = %d",headpos,mincy,absdiff(headpos,mincy));
		seekTime = seekTime + absdiff(maxcy,mincy);
		printf("\n%d - %d = %d",mincy,maxcy,absdiff(mincy,maxcy));
		seekTime = seekTime + absdiff(reqorder1[indexR],maxcy);
		printf("\n%d - %d = %d",maxcy,reqorder1[indexR],absdiff(reqorder1[indexR],maxcy));
	}
	printf("\nSeek Time = %d",seekTime);
}