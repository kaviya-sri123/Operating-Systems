#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct file_buffer 
{
	long mesg_type;
	char src[100];
	char dest[100];
}filename;

int main()
{
	key_t key;
	int msgid;	
	key = ftok("msgque", 65);
	if(key==-1)
	{
		perror("error");
	}
	else
	{
		msgid = msgget(key, 0666 | IPC_CREAT);
		filename.mesg_type = 1;	      
		
		printf("Enter source file : ");
		scanf("%s",filename.src);
		
		printf("Enter destination filename : ");
		scanf("%s",filename.dest);

		msgsnd(msgid, &filename, sizeof(filename), 0);

		printf("Source file: %s\n", filename.src);
		printf("Destination file: %s\n", filename.dest);
	}
	return 0;
}
