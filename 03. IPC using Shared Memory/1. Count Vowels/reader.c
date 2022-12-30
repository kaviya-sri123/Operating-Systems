#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

int vowelCount(char *str)
{   
    int count=0;     
    char vowel[] = {'a','A','e','E','i','I','o','O','u','U'};        
    int length = strlen(str);       
    for(int i=0;i<length;i++)       
    {                     
	    if (str[i] == 'a' || str[i] == 'A' || str[i] == 'e' || str[i] == 'E' || str[i] == 'i' || str[i] == 'I' || str[i] =='o' || str[i]=='O' || str[i] == 'u' || str[i] == 'U')                   
		 	count++;   
  	}        
	return count;
}

int main()
{
	key_t key = ftok("shmfile",65);
	if(key==-1)
	{
		perror("error");
	}
	int shmid = shmget(key, 1024, 0666|IPC_CREAT);
	char* str;
	str = (char*) shmat(shmid,(void*)0,0);
	printf("Data is: %s\n",str);
	int count = vowelCount(str);
	printf("Number Of vowels in given string is: %d\n",count);
	shmdt(str);
	shmctl(shmid,IPC_RMID,NULL);
}
