#include <stdio.h>
#include <stdlib.h>
void intSwap(int *a,int *b);
void floatSwap(float *a, float *b);
void FCFS(int n,int *pno,float *at,float *bt);
void SJF(int n,int *pno,float *at,float *bt);
void SRTF(int n,int *pno,float *at,float *bt);
void Priority(int n,int *pno,float *at,float *bt,int *priority);
void PreemptivePriority(int n,int *pno,float *at,float *bt,int *priority);
void RoundRobin(int n,int *pno,float *at,float *bt,float quantum);
void display(int n,int *pno,float *at,float *bt,float *wt,float *tat);
