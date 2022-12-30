#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<unistd.h>
#define size 5
#define mutex 0
#define full 1
#define empty 2

union semaphore
{
    int val;
    struct semid_ds *buf;
    struct seminfo *_buf;
    unsigned short *array;
};

void wait(int sid,int sno);
void signal(int sid,int sno);