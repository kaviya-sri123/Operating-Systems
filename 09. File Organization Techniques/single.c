#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char file[20][20];
int noOfFile,maxfile=10;
void insertFile(char *name)
{
 	if(noOfFile==maxfile)
	{
		printf("Maximum file limit reached\n");
		return;
 	}
 	int i;
 	for(i=0;i<noOfFile;i++)
	{
  		if(strcmp(file[i],name)==0)
		{
   			printf("Same filename not allowed\n");
   			return;
  		}
 	}
 	strcpy(file[noOfFile],name);
 	noOfFile+=1;
 	printf("File inserted\n");
}
void displayDir()
{
 	if(noOfFile==0)
  		printf("Empty directory!\n");
 	else
	{
  		printf("Files\n");
		for(int i=0;i<noOfFile;i++)
  			printf("%s\n",file[i]);
 	}
}
int main()
{
	int ch;
	char n[20];
 	do
 	{
		printf("-----------MENU-----------\n");
		printf("1 - Insert file\n");
  		printf("2 - Display directory\n");
		printf("3 - Exit\n");
		printf("--------------------------\n");
  		printf("Enter your choice: ");
  		scanf("%d",&ch);
  		switch(ch)
		{
   			case 1:
    			printf("Enter filename: ");
    			scanf("%s",n);
				insertFile(n);
				break;
   			case 2:
				displayDir();
				break;
			case 3:
				break;
  		}
 	}while(ch!=3);
 	return 0;
}