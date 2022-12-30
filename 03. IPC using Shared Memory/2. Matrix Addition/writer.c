#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<wait.h>

int main()
{
	int *a,*b,*dim,rows,cols;

    	key_t keyd = ftok("dim",101); 
    	int shmid_dim = shmget(keyd,1024,0666|IPC_CREAT);  
    	dim = (int*) shmat(shmid_dim,(void*)0,0);

	key_t key1 = ftok("mat1",102);
	int shmid1 = shmget(key1,1024,0666|IPC_CREAT);   
	a = (int*) shmat(shmid1,(void*)0,0);

	key_t key2 = ftok("mat2",103);
	int shmid2 = shmget(key2,1024,0666|IPC_CREAT);   
	b = (int*) shmat(shmid2,(void*)0,0);

	printf("Enter number of rows: ");   
    	scanf("%d",&rows);     
    	printf("Enter Number of columns: ");   
    	scanf("%d",&cols);

	dim[0] = rows;
	dim[1] = cols;
	dim[2] = 1;

	printf("Enter Matrix 1\n");
   	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			printf("Enter element %d %d: ",i+1,j+1);
			scanf("%d",(a+i*cols+j));
		}
	}    

	printf("Written data:\n"); 
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			printf("%d\t",*(a+i*cols+j));
		}
		printf("\n");
	}

    printf("Enter Matrix 2\n"); 
    for(int i=0;i<rows;i++)     
    {           
	    for(int j=0;j<cols;j++)     
    		{                  
		    printf("Enter element %d %d: ",i+1,j+1);   
  		    scanf("%d",(b+i*cols+j));          
	    }  
    }     

    printf("Written data:\n");  
    for(int i=0;i<rows;i++)   
    {             
	    for(int j=0;j<cols;j++)  
 	    {               
	      	printf("%d\t",*(b+i*cols+j));  
 	    }             
	    printf("\n");     
    }

    do
    {      
    }while(dim[2]==1);

    if(dim[2] == 0)  
    {
		shmdt(a);
		shmdt(dim);
		shmdt(b);
		shmctl(shmid_dim,IPC_RMID,NULL);
		shmctl(shmid1,IPC_RMID,NULL);
		shmctl(shmid2,IPC_RMID,NULL);
    }   

    return 0;
}
