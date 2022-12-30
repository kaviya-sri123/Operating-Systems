#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define size 50

int main()
{
    char arr_r[size], arr_w[size];
	int pipe1[2],pid;
	pipe(pipe1);
	pid = fork();
    	if(pid>0)
	{
		printf("Enter the string: ");
		scanf("%[^\n]s",arr_r);
		close(pipe1[0]);
		write(pipe1[1], arr_r, size);
        close(pipe1[1]);
	}
	else if(pid==0)
	{
		close(pipe1[1]);
		read(pipe1[0], arr_w, size);
        printf("String read from pipe is: %s\n",arr_w);
        close(pipe1[0]);
	}
	return 0;
}
