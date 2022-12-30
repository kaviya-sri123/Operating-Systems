#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
struct file_buffer
{
	long mesg_type;
	char src[100];
	char dest[100];
} filename;

int main()
{
	key_t key;
	int msgid;
	FILE *fileptr,*dest;
	char data[1000],ch;
	key = ftok("msgque", 65);
	if(key==-1)
	{
		perror("error");
	}
	else
	{

		msgid = msgget(key, 0666 | IPC_CREAT);
		msgrcv(msgid, &filename, sizeof(filename), 1, 0);		      
		printf("Source file: %s\n", filename.src);
		fileptr = fopen(filename.src, "r");
		if(fileptr == NULL)
		{
			perror("error");
		}
		else
		{
			printf("\nDestination file:%s\n",filename.dest);
			if(access(filename.dest, F_OK) ==0)
			{
				printf("File already exists.\n");
				return 0;
			}
			else
			{
				dest = fopen(filename.dest,"w");
				if(dest == NULL)
				{
					perror("error");
				}
				
				else
				{
					ch = fgetc(fileptr);
					while(ch !=EOF)
					{				
					fputc(ch,dest);
					ch = fgetc(fileptr);
					}
				}
				fclose(fileptr);
				fclose(dest);
				printf("\nData copied successfully.\n");
			}
			msgctl(msgid, IPC_RMID, NULL);
			return 0;
		}
	}
}
