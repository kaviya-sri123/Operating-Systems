#include<stdio.h>
struct file
{
    char name[20];
    int size;
};
struct block
{
    int size;
    int noOfBlocks;
    int flag;
};
int allocatefile(int freelist[],int blck,int file)
{
    int i,blcks,count=0,flag=0,start=0;
    for(i=start-1;i<blck;i++)
    {   
        if(freelist[i]!=0 && i==start-1)
            break;
        else
        {
            if(freelist[i]==1)
                count=0;
            else
                count++;
            if(count==file)
                flag=1;
        }
    }
    if(flag==1)
        return 1;
    else
    {   
	count=0;
        for(i=0;i<blck;i++)
        {
            if(freelist[i]==0)
            {
                count++;
                if(count==file)
                    break;
            }
            else
                count=0;
        }
        if(count==file)
            return 1; //allocated
        else
            return 0; //not allocated
    }
}
int main()
{
	int freelist[20],memsize,fileblocks,i,result;
	struct block blck;
	struct file file;
	printf("Enter the memory size (in bytes): ");
	scanf("%d",&memsize);
	printf("Enter the block size (in bytes): ");
	scanf("%d",&blck.size);
	blck.noOfBlocks=memsize/blck.size;
	printf("Number of blocks: %d\n",blck.noOfBlocks);
	printf("Enter the File Details\n");
	printf("Name: ");
	scanf("%s",file.name);
	printf("Size (in bytes): ");
	scanf("%d",&file.size);
	fileblocks=file.size/blck.size;
    	printf("Enter the free list\n");
    	printf("1-Allocated\t0-Unallocated\n");
    	for(i=0;i<blck.noOfBlocks;i++)
    	{   
		printf("Block %d: ",i+1);
        	scanf("%d",&freelist[i]);
    	}
  	if(file.size>memsize)
    		printf("File is not allocated\n");
  	else
    		result=allocatefile(freelist,blck.noOfBlocks,fileblocks);
	if(result==1)
		printf("File is allocated\n");
	else
		printf("File cannot be allocated\n");
    	return 0;
}
