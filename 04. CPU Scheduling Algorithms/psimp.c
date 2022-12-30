#include "pshdr.h"
void intSwap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void floatSwap(float *a,float *b)
{
    float temp=*a;
    *a=*b;
    *b=temp;
}
void FCFS(int n,int *pno, float *at,float *bt)
{
    int PNO[n];
    float AT[n],BT[n],START[n],CT[n],WT[n],TAT[n];
    for(int i=0;i<n;i++)
    {
        AT[i]=at[i];
        BT[i]=bt[i];
        PNO[i]=pno[i];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(AT[i]<AT[j])
            {
                intSwap(&PNO[i],&PNO[j]);
                floatSwap(&AT[i],&AT[j]);
                floatSwap(&BT[i],&BT[j]);
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(i==0)
            START[i]=AT[i];
        else
            START[i]=CT[i-1];

        WT[i]=START[i]-AT[i];
        CT[i]=START[i]+BT[i];
        TAT[i]=CT[i]-AT[i];
    }
    display(n,PNO,AT,BT,WT,TAT);
}
void SJF(int n,int *pno,float *at,float *bt)
{
    int PNO[n];
    float AT[n],BT[n],CT[n],WT[n],TAT[n];
    for(int i=0;i<n;i++)
    {
        AT[i]=at[i];
        BT[i]=bt[i];
        PNO[i]=pno[i];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
	        if(AT[i]>AT[j])
	        { 
                intSwap(&PNO[i],&PNO[j]);
	            floatSwap(&AT[i],&AT[j]);
                floatSwap(&BT[i],&BT[j]);
	        }
	        else if(AT[i]==AT[j])
	        {
	            if(BT[i]>BT[j])
                {
                    intSwap(&PNO[i],&PNO[j]);
                    floatSwap(&AT[i],&AT[j]);
                    floatSwap(&BT[i],&BT[j]);
                }
	        }
       }
    }
    CT[0]=AT[0] + BT[0];
    float min = 1000;
    int pos;
    for(int i=1;i<n;i++)
    {
        for(int j=i;j<n;j++)
        {
            if(AT[j]<=CT[i-1])
            {
                if(BT[j]<min)
                {
                    min=BT[j];
                    pos=j;
                }
            }
        }
        intSwap(&PNO[i],&PNO[pos]);
        floatSwap(&AT[i],&AT[pos]);
        floatSwap(&BT[i],&BT[pos]);
        min=1000;
        CT[i]=CT[i-1]+BT[i];
    }
    for(int i=0;i<n;i++)
    {
        TAT[i]=CT[i]-AT[i];
        WT[i]=TAT[i]-BT[i];
    }
    display(n,PNO,AT,BT,WT,TAT);
}
void SRTF(int n,int *pno,float *at,float *bt)
{
    int PNO[n],RT[n];
    float AT[n],BT[n],CT[n],WT[n],TAT[n];
    float total=0;
    for(int i=0;i<n;i++)
    {
        AT[i]=at[i];
        BT[i]=bt[i];
        RT[i]=bt[i];
    }
    int smallest,remain=0;
    float endTime,time;
    float totwt=0,tottat=0;
    //Find maximum burst time
    int maxBT = 0;
    for(int i=0;i<n;i++)
        if(BT[i]>maxBT)
            maxBT=BT[i];
    for(time=0;remain!=n;time++)
    {
        smallest=n+1; //Arbitrarily use a memory location for comparing
        RT[smallest]=maxBT+1; //Assign it with maximum burst time
        for(int i=0;i<n;i++)
        {
            if(AT[i]<=time && RT[i] < RT[smallest] && RT[i]>0)
            {
                smallest=i;
            }
        }
        RT[smallest]--;
        if(RT[smallest]==0)
        {
            remain++;
            endTime=time+1;
            PNO[smallest]=smallest+1;
            WT[smallest]=endTime-bt[smallest]-at[smallest];
            TAT[smallest]=endTime-at[smallest];
        }
    }
    display(n,PNO,AT,BT,WT,TAT);
}
void Priority(int n,int *pno,float *at,float *bt,int *priority)
{
    int PNO[n],PRI[n];
    float AT[n],BT[n],CT[n],WT[n],TAT[n];
    int N=n,time=0;
    float totwt=0,tottat=0;
    for(int i=0;i<n;i++)
    {
        PNO[i]=pno[i];
        AT[i]=at[i];
        BT[i]=bt[i];
        PRI[i]=priority[i];
    }
    for(int i=1;i<N;i++) 
    {
        for(int j=0;j<N-i;j++) 
        {
            if(AT[j] > AT[j+1]) 
            {
                intSwap(&PNO[j],&PNO[j+1]);
                floatSwap(&AT[j],&AT[j+1]);
                floatSwap(&BT[j],&BT[j+1]);
                intSwap(&PRI[j],&PRI[j+1]);
            }
        }
    }
    for(int i=2;i<n;i++)
    {
        for(int j=1;j<n-i+1;j++)
        {
            if(PRI[j] > PRI[j+1])
            {
                intSwap(&PNO[j],&PNO[j+1]);
                floatSwap(&AT[j],&AT[j+1]);
                floatSwap(&BT[j],&BT[j+1]);
                intSwap(&PRI[j],&PRI[j+1]);
            }
        }
    }
    totwt = WT[0] = 0;
    tottat = TAT[0] = BT[0] - AT[0];
    for(int i=1;i<n;i++)
    {
        WT[i] = (BT[i-1] + AT[i-1] + WT[i-1]) - AT[i];
        TAT[i] = (WT[i] + BT[i]);
    }
    display(n,PNO,AT,BT,WT,TAT);
}
void PreemptivePriority(int n,int *pno,float *at,float *bt,int *priority)
{
    int PNO[n],PRI[n];
    float AT[n],BT1[n],BT2[n],CT[n],WT[n],TAT[n];
    float totwt=0,tottat=0;
    for(int i=0;i<n;i++)
    {
        PNO[i]=pno[i];
        AT[i]=at[i];
        BT1[i]=BT2[i]=bt[i];
        PRI[i]=priority[i];
    }
    
    //Find process with least priority
    int minPriority = 0; 
    for(int i=0;i<n;i++)
        if(PRI[i]>minPriority)
            minPriority=PRI[i];
    
    int count=0,smallest;
    float t;
    for(t=0;count!=n;t++)
    {
        smallest=n+1; //Arbitrarily use a memory location for comparing
        PRI[n+1]=minPriority+1; //Assign it with least priority
        for(int i=0;i<n;i++)
        {
            if(PRI[smallest]>PRI[i] && AT[i]<=t && BT1[i]>0)
            {
                smallest=i;
            }
        }
        BT1[smallest]=BT1[smallest]-1;
        if(BT1[smallest]==0)
        {
            count++;
            WT[smallest]=t+1-AT[smallest]-BT2[smallest];
            TAT[smallest]=t+1-AT[smallest];  
        }
    }
    display(n,pno,AT,BT2,WT,TAT);
}
void RoundRobin(int n,int *pno,float *at,float *bt,float quantum)
{
    int PNO[n];
    float AT[n],BT[n],RT[n],CT[n],PRI[n],WT[n],TAT[n];
    int i,flag=0,remain=n;
    float totwt=0,tottat=0,time=0;
    for(i=0;i<n;i++)
    {
        PNO[i]=pno[i];
        AT[i]=at[i];
        BT[i]=RT[i]=bt[i];
    }
    for(i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(AT[i] > AT[j])
            {
                intSwap(&PNO[i],&PNO[j]);
                floatSwap(&AT[i],&AT[j]);
                floatSwap(&BT[i],&BT[j]);
                floatSwap(&RT[i],&RT[j]);
            }
        }
    }
    
    for(time=0,i=0;remain!=0;)
    {
        if(RT[i]<=quantum && RT[i]>0)
        {
            time += RT[i];
            RT[i] = 0;
            flag = 1;
        }
        else if(RT[i]> 0)
        {
            RT[i]-=quantum;
            time += quantum;
        }
        if(RT[i]==0 && flag==1)
        {
            remain--;

            TAT[i] = time-AT[i];
            WT[i]= time-AT[i]-BT[i];
            flag=0;
        }
        if(i==n-1)
            i=0;
        else if(AT[i] <= time)
            i++;
        else
            i=0;
    }
    display(n,PNO,AT,BT,WT,TAT);
}
void display(int n,int *PNO,float *AT,float *BT,float *WT,float *TAT)
{
    float totwt=0,tottat=0;
    printf("Process  Arrival-time(s)  Burst-time(s)  Waiting-time(s)  Turnaround-time(s)\n");
    for(int i=0;i<n;i++)
    {
		printf("P%d\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",PNO[i],AT[i],BT[i],WT[i],TAT[i]);
        totwt+=WT[i];
        tottat+=TAT[i];
    }
	printf("\n\nAverage Waiting Time = %0.2f\n",totwt/n);
	printf("Average Turn-Around Time = %0.2f\n\n",tottat/n);
}
