#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct deadlock
{
	int **allocation;
	int *available;
	int **max;
	int **need;
};

int safetyAlgorithm(struct deadlock* d,int n,int m);
int resourceRequest(struct deadlock* d,int n,int m,int p,int* request);
void display(struct deadlock* d,int n,int m);
