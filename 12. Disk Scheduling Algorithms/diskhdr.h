#include <stdio.h>
#include <stdlib.h>
int absdiff(int a,int b);
int* sort(int *arr,int n);
void FCFS(int ncyl,int nreq,int *reqorder,int headpos);
void SSTF(int ncyl,int nreq,int *reqorder,int headpos);
void SCAN(int ncyl,int nreq,int *reqorder,int headpos,int prevheadpos);
void CSCAN(int ncyl,int nreq,int *reqorder,int headpos,int prevheadpos);
void LOOK(int ncyl,int nreq,int *reqorder,int headpos,int prevheadpos);
void CLOOK(int ncyl,int nreq,int *reqorder,int headpos,int prevheadpos);