#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    pid_t pid;
    pid=fork();
    if(pid<0)
    {
        printf("Error.\n");
    }
    else if (pid==0)
    {
        printf("Child.");
        execlp("/usr/bin/ls","ls",NULL);
    }
    else
    {
        wait(NULL);
        printf("Parent.");
    }
    return 0;
}
