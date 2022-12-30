#include <stdio.h>
#include <stdlib.h>
int FIFO(int refsize,int *reflist,int framesize);
int LRU(int refsize,int *reflist,int framesize);
int OPTIMAL(int refsize,int *reflist,int framesize);
void BEST(int refsize,int *reflist,int framesize);