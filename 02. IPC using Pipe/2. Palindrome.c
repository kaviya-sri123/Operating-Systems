#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>

void isPalindrome(char *string)
{
	char *ptr,*rev;
	ptr = string;
	while (*ptr != '\0')
	{
		++ptr;
	}
	--ptr; 
	for(rev = string; ptr >= rev;rev++)
	{
		if (*ptr == *rev)
		{
			--ptr;
		}
		else
		    break;
	}
	if (rev > ptr)
		printf("\n%s is palindrome.",string);
	else
		printf("\n%s is not a palindrome.",string);
}



int main()
{
	int n,id,fds[2];
	char *wm,*rm;
	char buffer;
	int rs=pipe(fds);
	printf("Enter string length: ");
	scanf("%d%c",&n,&buffer);
	wm = (char*)malloc(n * sizeof(char));
	printf("Enter string: ");
	scanf("%[^\n]s", wm);
	rm = (char*)malloc(n * sizeof(char));
	id=fork();
	if(id==0)
	{
		close(fds[1]);
		read(fds[0],rm,strlen(wm));
		printf("\nChild Process:");
		isPalindrome(rm);
		close(fds[0]);
	}
	else
	{
		close(fds[0]);
		write(fds[1],wm,strlen(wm));
		wait(NULL);
		printf("\nParent Process:");
		printf("\n%s\n",wm);
		close(fds[1]);
	}
	return 0;
}
