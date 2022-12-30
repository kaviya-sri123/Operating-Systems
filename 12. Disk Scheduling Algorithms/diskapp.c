#include "diskhdr.h"
int main()
{
	int ncyl,nreq,headpos,ch,result,prevheadpos;
	printf("Enter the total number of cylinders: ");
	scanf("%d",&ncyl);
	printf("Enter the number of requests: ");
	scanf("%d",&nreq);
	int *reqorder = (int*)malloc(nreq*sizeof(int));
	printf("Enter the order of requests: ");
 	for(int i=0;i<nreq;i++)
  		scanf("%d",&reqorder[i]);
	printf("Enter the head position: ");
	scanf("%d",&headpos);
	printf("Enter the previous head position: ");
	scanf("%d",&prevheadpos);
 	do
 	{
		printf("\n==================MENU==================");
		printf("\n1 -> FCFS Disk Scheduling Algorithm");
		printf("\n2 -> SSTF Disk Scheduling Algorithm");
		printf("\n3 -> SCAN Disk Scheduling Algorithm");
		printf("\n4 -> CSCAN Disk Scheduling Algorithm");
		printf("\n5 -> LOOK Disk Scheduling Algorithm");
		printf("\n6 -> CLOOK Disk Scheduling Algorithm");
		printf("\n7 -> EXIT");
		printf("\n========================================");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
  		switch(ch)
  		{
			case 1:
				FCFS(ncyl,nreq,reqorder,headpos);
				break;
   			case 2:
    			SSTF(ncyl,nreq,reqorder,headpos);
				break;
   			case 3:
    			SCAN(ncyl,nreq,reqorder,headpos,prevheadpos);
    			break;
			case 4:
				CSCAN(ncyl,nreq,reqorder,headpos,prevheadpos);
				break;
   			case 5:
				LOOK(ncyl,nreq,reqorder,headpos,prevheadpos);
				break;
			case 6:
				CLOOK(ncyl,nreq,reqorder,headpos,prevheadpos);
				break;
			case 7:
				break;
			default:
				printf("\nEnter a valid choice.\n");
				break;
  		}
 	}while(ch!=7);
	return 0;
}