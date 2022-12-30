#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/shm.h>
int sum(int* arr, int begin, int end)
{
	int sum=0;
	for(int i=begin;i<end;i++)
		sum+=arr[i];
	return sum;
}
int main()
{
	int *num,n,size;
	do
	{
		printf("Enter total numbers: ");
		scanf("%d",&n);
		if(n%4!=0)
		{
			printf("Enter number of elements divisible by 4\n");
		}
		else
		{
			size = n/4;
			break;
		}
	}while(1);
	key_t key = ftok("shmfile",151);
	if(key==-1)
	{
		perror("error");
	}
	else
	{
		int shmid = shmget(key, 1024, IPC_CREAT | 0666);
		num =(int*)shmat(shmid,(void *)0,0);
		for(int i=0;i<n;i++)
		{
			printf("Enter element %d: ",i+1);
			scanf("%d",&num[i]);		
		}
		pid_t id1,id2,id3;
		id1=fork();
		if(id1==0)
		{
			num[n+1] = sum(num,size,2*size);
			id2=fork();
			wait(NULL);
			if(id2==0)   
		   	{              
				num[n+2] = sum(num,2*size,3*size);
				id3=fork();
				wait(NULL);
				if(id3==0)
				{           
					num[n+3] = sum(num,3*size,4*size);
				}
			}
		}
		else 
		{
			num[n] = sum(num,0,size);
			wait(NULL);
			printf("Sum from Process P1:%d\n", num[n]);
			printf("Sum from Process P2:%d\n", num[n+1]);
			printf("Sum from Process P3:%d\n", num[n+2]);
			printf("Sum from Process P4:%d\n", num[n+3]); 
 			shmdt(num);
		}	
		shmctl(shmid, IPC_RMID, NULL);
	}
	return 0;
}
