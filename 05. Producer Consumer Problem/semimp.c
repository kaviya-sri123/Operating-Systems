#include "semhdr.h"

void wait(int sid,int sno)
{
    int a;
    struct sembuf s;
    s.sem_num=sno;
    s.sem_op=-1;
    s.sem_flg=SEM_UNDO;
    a=semop(sid,&s,1);
}

void signal(int sid,int sno)
{
    int a;
    struct sembuf s;
    s.sem_num=sno;
    s.sem_op=1;
    s.sem_flg=SEM_UNDO;
    a=semop(sid,&s,1);
}