#include "pagehdr.h"

int main()
{
   int framesize,refsize,*reflist,ch,result;
   printf("Enter the length of the reference string: ");
   scanf("%d",&refsize);
   reflist = (int*)malloc(refsize*sizeof(int));
   printf("Enter the reference string: ");
   for(int i=0;i<refsize;i++)
      scanf("%d",&reflist[i]);
   do
   {
      printf("\n==========MENU==========\n");
		printf("1 -> FIFO\n");
		printf("2 -> LRU\n");
		printf("3 -> OPTIMAL\n");
		printf("4 -> BEST ALGORITHM\n");
  		printf("5 -> EXIT\n");
		printf("=========================\n");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
      switch(ch)
      {
         case 1:
            printf("Enter frame size: ");
            scanf("%d",&framesize);
            result=FIFO(refsize,reflist,framesize);
            break;
         case 2:
            printf("Enter frame size: ");
            scanf("%d",&framesize);
            result=LRU(refsize,reflist,framesize);  
            break;
         case 3:
            printf("Enter frame size: ");
            scanf("%d",&framesize);
            result=OPTIMAL(refsize,reflist,framesize);
            break;
         case 4:
            printf("Enter frame size: ");
            scanf("%d",&framesize);
            BEST(refsize,reflist,framesize);
            break;
         case 5:
				break;
			default:
				printf("Enter a valid choice.\n");
      }
   }while(ch!=5);
}