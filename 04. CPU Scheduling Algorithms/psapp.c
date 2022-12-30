#include "pshdr.h"
int main()
{
    int n,ch;
    printf("Enter total number of processes: ");
    scanf("%d",&n);
    int pno[n],priority[n];
    float at[n],bt[n];
    float quantum;
    for(int i=0;i<n;i++)
    {
        pno[i]=i+1;
        printf("Process %d\n",i+1);
        printf("Enter Arrival Time: ");
        scanf("%f",&at[i]);
        printf("Enter Burst Time: ");
        scanf("%f",&bt[i]);
        printf("Enter Priority: ");
        scanf("%d",&priority[i]);
    }
    do
    {
        printf("\n======================MENU======================");
        printf("\n1 -> FCFS Scheduling Algorithm");
        printf("\n2 -> SJF Scheduling Algorithm");
        printf("\n3 -> SRTF Scheduling Algorithm");
        printf("\n4 -> Priority Scheduling Algorithm");
        printf("\n5 -> Preemptive Priority Scheduling Algorithm");
        printf("\n6 -> Round Robin Scheduling Algorithm");
        printf("\n7 -> EXIT");
        printf("\n================================================");
        printf("\nEnter the choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                FCFS(n,pno,at,bt);
                break;
            case 2:
                SJF(n,pno,at,bt);
                break;
            case 3:
                SRTF(n,pno,at,bt);
                break;
            case 4:
                Priority(n,pno,at,bt,priority);
                break;
            case 5:
                PreemptivePriority(n,pno,at,bt,priority);
                break;
            case 6:
                printf("Enter time quantum: ");
                scanf("%f",&quantum);
                RoundRobin(n,pno,at,bt,quantum);
                break;
            case 7:
                break;
            default:
                printf("\nEnter a valid choice.\n");
        }
    }while(ch!=7);
}
