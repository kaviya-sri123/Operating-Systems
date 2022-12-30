#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct FileNode
{
    char *fileName;
    char *text;
    struct FileNode *next;
    struct FileNode *child;
};

struct DirTree
{
    struct FileNode *root;
};

char* copyString(char s[])
{
    char* s2;
    s2 = (char*)malloc(100);
    strcpy(s2, s);
    return (char*)s2;
}

struct FileNode* newFileNode(char *f,char *t)
{
    struct FileNode* fn =(struct FileNode*)malloc(sizeof(struct FileNode));
    fn->fileName = copyString(f);
    fn->text = copyString(t);
    fn->next=NULL;
    fn->child= NULL;
    return fn;
}

struct DirTree* createDirTree()
{
    struct DirTree* q=(struct DirTree*)malloc(sizeof(struct DirTree));
    struct FileNode* fn = newFileNode("root","");
    q->root=fn;
    return q;
}

void enqueueUser(struct DirTree *q,struct FileNode* newNode) //enqueue User
{
    struct FileNode* temp = q->root;
    struct FileNode* tempU;
    if(temp->child == NULL)
    {
        //No user in directory
        temp->child = newNode;
        printf("User Created\n");
        return;
    }
    else
    {
        //directory has users
        tempU = temp->child;
        while(tempU->next!=NULL && (strcmp(tempU->fileName,newNode->fileName)!=0))
            tempU = tempU->next;
        if(strcmp(tempU->fileName,newNode->fileName)==0)
        {
            //same user name
            printf("User Already Exist\n");
            return;
        }
        tempU->next = newNode;
        printf("User Created\n");
        return;
    }
}

void SaveFile(struct FileNode* f,struct FileNode* newNode) //save file in sub directory
{
    struct FileNode* temp = f;
    while(temp->next!=NULL && (strcmp(temp->fileName,newNode->fileName)!=0))
        temp = temp->next;
    if(strcmp(temp->fileName,newNode->fileName)==0)
    {
        //same file name
        printf("File Already Exist\n");
        return;
    }
    temp->next = newNode;
    printf("File Created\n");
    return;
}

void enqueueFile(struct DirTree *f,char *user,struct FileNode* newNode) //Enqueue File
{
    int choice;
    char name[10];
    struct FileNode *tempU = f->root->child;
    while(tempU->next != NULL && (strcmp(tempU->fileName,user)!=0)) //find User
        tempU = tempU->next;
    if(tempU->child==NULL)
    {
        //no file in user
        tempU->child=newNode;
        printf("File Inserted\n");
        return;
    }
    SaveFile(tempU->child,newNode);
}

void display(struct FileNode *f,int space)
{
    if(f->child == NULL)
    {
        for(int i=0;i<space;i++)
            printf("-");
        printf("%s\n",f->fileName);
        space-=3;
        return;
    }
    else
    {
        for(int i=0;i<space;i++)
            printf("-");
        printf("%s\n",f->fileName);
        struct FileNode *temp = f->child;
        space+=3;
        while(temp!=NULL)
        {
            display(temp,space);
            temp=temp->next;
        }
    }
}

void displayFile(struct DirTree *d)
{
    struct FileNode *temp = d->root;
    struct FileNode *tempF;
    if(temp->child == NULL)
    {
        printf("Empty\n");
        return;
    }
    temp = temp->child;
    int space;
    while(temp!=NULL)
    {
        printf("User : %s\n",temp->fileName);
        if(temp->child==NULL)
            printf("No File inside\n");
        else
        {
            tempF = temp->child;
            while(tempF!=NULL)
            {
                printf("Filename: %s | Content: %s\n",tempF->fileName,tempF->text);
                tempF=tempF->next;
            }
        }
        temp=temp->next;
    }
}

int main()
{
    int ch;
    char n[10],un[10],t[100];
    struct DirTree *d = createDirTree();
    struct FileNode *fn;
    do
    {
        printf("------------MENU------------\n");
        printf("1 -> Create User\n");
        printf("2 -> Insert File\n");
        printf("3 -> Display File Directory\n");
        printf("4 -> Exit\n");
        printf("-----------------------------\n");
        printf("Enter the Choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("Enter User Name : ");
                scanf("%s",n);
                fn = newFileNode(n,"");
                enqueueUser(d,fn);
                break;
            case 2:
                printf("Enter User Name : ");
                scanf("%s",un);
                printf("Enter File Name : ");
                scanf("%s",n);
                getchar();
                printf("Enter File Content : ");
                fgets(t,100,stdin);
                fn = newFileNode(n,t);
                enqueueFile(d,un,fn);
                break;
            case 3:
                displayFile(d);
                break;
            case 4:
                break;
            default:
                break;
        }
    }while(ch!=4);
    return 0;
}
