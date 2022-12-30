#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	key_t key = ftok("shmfile",65);
	if(key==-1)
	{
		perror("error");
	}
	int shmid = shmget(key,1024,0666|IPC_CREAT);
	char *str = (char*) shmat(shmid,(void*)0,0);
	printf("Enter the string: ");
	scanf("%[^\n]s",str);
	printf("Written data: %s\n",str);
	shmdt(str);
	return 0;
}
