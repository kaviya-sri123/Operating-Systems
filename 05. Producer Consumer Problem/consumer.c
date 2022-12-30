#include "semhdr.h"
int main()
{
    union semaphore snum;
    int out=0,num;
    unsigned short a[3];
    key_t key=ftok("shmfile",65);
    if(key==-1) perror("error");
    int s1=shmget(key,sizeof(int)*size,IPC_EXCL|00600);
    if(s1==-1) perror("shmget");
    int *buf=(int*)shmat(s1,NULL,00600);
    if(buf==NULL) perror("shmat");
    int sid=semget(5777,3,00600);
    if(sid==-1) perror("semget");
    a[0]=1;
    a[1]=0;
    a[2]=size;
    snum.array=a;
    semctl(sid,0,SETALL,snum);
    printf("Consumer waiting\n");
    for(int i=0;i<size;i++)
    {
        wait(sid,full);
        wait(sid,mutex);
        num=buf[out%size];
        out++;
        signal(sid,mutex);
        signal(sid,empty);
        printf("Square of %d is %d\n",num,num*num);
    }
}