#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

int main()
{   
	int *a,*b,*dim,*sum,rows,cols;
	
	key_t keyd = ftok("dim",101);
	int shmid_dim = shmget(keyd, 1024, 0666|IPC_CREAT);
	dim =(int*)shmat(shmid_dim,(void*)0, 0);

	key_t key1 = ftok("mat1",102);
	int shmid1 = shmget(key1, 1024, 0666|IPC_CREAT);   
	a = (int*)shmat(shmid1,(void*)0,0);  

	key_t key2 = ftok("mat2",103);
	int shmid2 = shmget(key2, 1024, 0666|IPC_CREAT);
	b =(int*)shmat(shmid2,(void*)0,0);

	rows = dim[0];
	cols = dim[1];
	sum=(int*)malloc(rows*cols*sizeof(int));

	printf("Matrix 1\n");
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
		    printf("%d\t",*(a+i*cols+j));
	    }
	    printf("\n");
	}

	printf("\nMatrix 2\n");
	for(int i=0;i<rows;i++)  
  	{      
      	for(int j=0;j<cols;j++)  
  		{             
	     	printf("%d\t",*(b+i*cols+j));    
    	}            
	    printf("\n");   
   	}

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			*(sum+(i*cols)+j) = *(a+(i*cols)+j)+*(b+(i*cols)+j);
		}
	}

	printf("\nSum of two matrices\n");
	for(int i=0;i<rows;i++)   
 	{               
	 	for(int j=0;j<cols;j++)  
		{                   
      		printf("%d\t",*(sum+i*cols+j));    
		}                    
		printf("\n");        
    }
	dim[2]=0;
	shmdt(a);
	shmdt(dim);
	shmdt(b);
	return 0;
}
