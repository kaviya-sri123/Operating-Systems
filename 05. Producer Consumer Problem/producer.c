#include "semhdr.h"
int main()
{
    union semaphore snum;
    int in=0,num;
    unsigned short a[3];
    key_t key=ftok("shmfile",65);
    if(key==-1) perror("error");
    int s1=shmget(key,sizeof(int)*size,IPC_CREAT|IPC_EXCL|00600);
    if(s1==-1) perror("shmget");
    int *buf=(int*)shmat(s1,NULL,00600);
    if(buf==NULL) perror("shmat");
    int sid=semget(5777,3,IPC_CREAT|00600);
    if(sid==-1) perror("semget");
    a[0]=1;
    a[1]=0;
    a[2]=size;
    snum.array=a;
    semctl(sid,0,SETALL,snum);
    for(int i=0;i<size;i++)
    {
        printf("Enter the number: ");
        scanf("%d",&num);
        wait(sid,empty);
        wait(sid,mutex);
        buf[in%size]=num;
        in++;
        signal(sid,mutex);
        signal(sid,full);
    }
    semctl(sid,0,IPC_RMID);
    shmctl(s1,IPC_RMID,NULL);
}