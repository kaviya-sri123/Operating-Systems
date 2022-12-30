#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int fd1[2],fd2[2];
    int id1;
    int p1=pipe(fd1);
    if(p1==0)
    {
        printf("Pipe p1 sucessfully created.\n");
    }
    char rm[100],wm[100];
    int flag=1,i,j=0;
    int p2=pipe(fd2);
    if(p2==0)
    {
        printf("Pipe p2 sucessfully created.\n");
    }
    id1=fork();
    if(id1>0)
    {
        close(fd1[0]);
        close(fd2[1]);
        do
        {
            if(flag!=0)
            {
                printf("Parent -> Enter the message: ");
                gets(wm);
                write(fd1[1],wm,strlen(wm)+1);
                if(!strcmp(wm,"bye"))
                {
                    flag=0;
                }
                read(fd2[0],rm,25);
                if(!strcmp(rm,"bye"))
                {
                    flag=0;
                }
            }
        }while(flag!=0);
        close(fd1[1]);
        close(fd2[0]);
    }
    else if(id1==0)
    {
        close(fd1[1]);
        close(fd2[0]);
        do
        {
            read(fd1[0],rm,25);
            if(!strcmp(rm,"bye"))
            {
                flag=0;
            }
            if(flag!=0)
            {
                printf("Child -> Enter the message: ");
                gets(wm);
                write(fd2[1],wm,strlen(wm)+1);
                if(!strcmp(wm,"bye"))
                {
                    flag=0;
                }
            }
        }while(flag!=0);
        close(fd1[0]);
        close(fd2[1]);
    }
    else
    {
        printf("\nChild process not created.");
    }
}
