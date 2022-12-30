#include "memoryhdr.h"

int main()
{
 	int nm,np,ch,t;
	printf("Enter the number of memory fragments: ");
	scanf("%d",&nm);
	int memory[nm];
	printf("Enter the memory sizes: ");
	for(int i=0;i<nm;i++)
		scanf("%d",&memory[i]);
	printf("Enter the number of processes: ");
	scanf("%d",&np);
	int process[np];
 	for(int i=0;i<np;i++)
	{
		printf("Enter memory size of process P%d: ",i);
		scanf("%d",&process[i]);
 	}
 	do
 	{
		printf("\n==========MENU==========\n");
		printf("1 -> First fit\n");
		printf("2 -> Best fit\n");
		printf("3 -> Worst fit\n");
		printf("4 -> Optimum technique\n");
  		printf("5 -> Exit\n");
		printf("=========================\n");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
  		switch(ch)
		{
			case 1:
				t = firstFit(nm,memory,np,process);
				break;
   			case 2:
    			t = bestFit(nm,memory,np,process);
    			break;
   			case 3:
    			t = worstFit(nm,memory,np,process);
    			break;
   			case 4:
    			optimumFit(nm,memory,np,process);
    			break;
			case 5:
				break;
			default:
				printf("Enter a valid choice.\n");
  		}
 	}while(ch!=5);
}