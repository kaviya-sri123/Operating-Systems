#include <stdio.h>
#include <stdlib.h>
void HoldAndWait(int n,int m,int *available,int allocation[n][m])
{
    int available1[m],skipped,count=0,completed=0,finish[n],done[n];
	for(int i=0;i<m;i++)
		available1[i]=available[i];

	for(int i=0;i<n;i++)
		done[i]=-1;
    while(n != completed)	//skipped should not be equal to the all remaining process - means unsafe
	{
		skipped = 0;
		for(int i=0;i<n;i++)
		{
			if(done[i] != -1) //already completed
			{
				skipped++;
				continue;
			}

			for(int j=0;j<m;j++)
				if(allocation[i][j] <= available[j])
					count++;

			if(count=m)	//process i can be allocated
			{
				for(int j=0;j<m;j++)
					available[j] -= allocation[i][j];
				finish[completed++] = i+1;
				done[i]=1;
				skipped=0;
			}
			else
				skipped++;
			count=0;
		}
		//wait till all resources are released
		printf("All allocated resources freed\n");
		for(int i=0;i<m;i++)
			available[i] = available1[i];
	}
	printf("Order of resource allocation: ");
	for(int i=0;i<n;i++)
		printf("P%d ", finish[i]);
    printf("\n");
}
void CircularWait(int n,int m,int *available)
{
	int pid,available1[m];
	for(int i=0;i<m;i++)
		available1[i]=available[i];
    do
	{
		int rid=-1, t_rid;
		printf("Enter the process ID (Enter 0 to exit): ");
		scanf("%d", &pid);
		if(pid==0)
			break;
		printf("============\n");
		printf("Process P%d\n",pid);
		printf("============\n");
		do
		{
			printf("Enter the resource number to allocate (Enter 0 to exit): ");
			scanf("%d",&t_rid);
			if(t_rid == 0)	//exit choice
				break;
			else if(t_rid <= rid)	//requested lower priority resource or unavailable resource
			{
				printf("Can't allocate lower priority resource for this process.\n");
				break;
			}
			else	//resource allocated
			{
				rid = t_rid;
				printf("Resource allocated\n");
			}
		}while(t_rid != 0);
	}while(pid != 0);
}
int main()
{
    int ch,n,m;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("Enter the number of resources types: ");
    scanf("%d",&m);
	int available[m],allocation[n][m];
	printf("=================Resource Instances=================\n");
    for(int i=0;i<m;i++)
	{
		printf("Number of instances for resource %d: ", i+1);
		scanf("%d",&available[i]);
	}
    printf("===================================================\n");
    do
    {
        printf("==========MENU==========\n");
        printf("1 -> Hold and Wait\n");
        printf("2 -> Circular wait\n");
        printf("3 -> Exit         \n");
        printf("========================\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
				printf("================Resource Allocation================\n");
				for(int i=0;i<n;i++)
				{
					printf("============\n");
					printf("Process P%d\n",i+1);
					printf("============\n");
					for(int j=0;j<m;j++)
					{
						printf("Number of instances of resource %d to allocate: ", j+1);
						scanf("%d",&allocation[i][j]);
					}
				}
				printf("==================================================\n");
                HoldAndWait(n,m,available,allocation);
                break;
            case 2:
                CircularWait(n,m,available);
                break;
            case 3:
                break;
            default:
                printf("Enter a valid choice.\n");
                break;
        }
    }while(ch!=3);
}