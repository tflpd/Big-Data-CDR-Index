#ifndef LISTH
#define LISTH

#include <stdio.h>
#include <stdlib.h>
#include "hashStructs.h"

/*struct to have a number and his origin together*/
typedef struct mergedNum
{
	int origin;
	long int number;
} mergedNum;

typedef struct listNode {
	mergedNum number;
	struct listNode *next;
} listNode;

typedef struct List {
	listNode * head;
}List;

/*List creation and initialization*/
List *listCreate();

/*Node creation and initialization*/
listNode *listNodeCreate(int origin, long int num);

/*Appends at the and of the list if the number is not found otherwise just passes to avoid dublicates*/
void listAppend(List *list, int origin, int long num);

/*Memory deallocation of the list*/
void listDestroy(List *list);

/*Appends to list L a callee if he is found earlier and not already in list*/
void findContacts1(List *L, Bucket *tmpNumBucket, int numPosition);

/*Appends to list L a callee if he is found earlier and not already in list*/
void findContacts2(List *L, Bucket *tmpNumBucket, int numPosition);

/*Merges the list L! and the list L! to list mergedList avoiding again the dublicates*/
void mergeLists(List *L1, List *L2, List *mergedList);

/*Checks if any number of list L1 is member of list L2, if yes  it returns 0 else 1*/
int notContacted(List *L1, List *L2);
#endif
