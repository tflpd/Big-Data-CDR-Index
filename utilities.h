#ifndef UTILITIES
#define UTILITIES

#include <stdio.h>
#include <stdlib.h>

#include "stringManipulate.h"
#include "hashStructs.h"
#include "findFuncs.h"
#include "list.h"
#include "setters.h"

/*Implementing the requested function print*/
void printHashT(Bucket **hashTable, int entries);

/*Implementing the requested function dump*/
void dumpHashT(Bucket **hashTable, int entries, FILE *fp);

/*Implementing the requested function find/lookup*/
void find(int argCounter, char **args, Bucket *tmpNumBucket, int numPosition);

/*Implementing the requested function topDest*/
void topDest(Bucket *tmpNumBucket, int numPosition);

/*Implementing the requested function indist*/
void indist(char *num1, char *num2, Bucket **hashTable1, Bucket **hashTable2, int callerHashEntries, int calleeHashEntries);

/*Implementing the requested function bye/exit*/
void freeMemory(int mode, Bucket **hashTable1, Bucket **hashTable2, int callerHashEntries, int calleeHashEntries);

#endif