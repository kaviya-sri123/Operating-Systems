#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
    pid_t pid;
    int n;
    printf("Enter n: ");
    scanf("%d",&n);
    pid = fork();
    
    if(pid==0)
    {
        //Child Process P2
        while(n!=1)
        {
            if(n%2==0)
            {
                n=n/2;
                printf("%d ",n);
            }
            else
            {
                n=3*n + 1;
                printf("%d ",n);
            }
        }
    }
    else
    {
        //Parent Process P1
        wait(NULL);
        printf("\nSum of first %d natural numbers is: %d\n",n,(n*(n+1))/2);
    }
    return 0;
}
