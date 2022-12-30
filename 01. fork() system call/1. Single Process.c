#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
    pid_t id1;
    pid_t p1,p2;
    id1 = fork();
    if(id1==0)
    {
        //Child Process P2
        p1 = getppid();
        p2 = getpid();
        printf("Child process P2\n");
        printf("Process ID: %d Parent ID: %d\n",p2,p1);
    }
    else
    {
        //Parent Process P1
        p1 = getppid();
        p2 = getpid();
        printf("Parent process P1\n");
        printf("Process ID: %d Parent ID: %d\n",p2,p1);
    }
    return 0;
}
