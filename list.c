#include "list.h"

List * listCreate() {
	List* list = realloc(NULL, sizeof(List));
	list->head = NULL;
	return list;
}

listNode * listNodeCreate(int origin, long int num) {
	listNode* newNode = realloc(NULL, sizeof(listNode));
	newNode->number.origin = origin;
	newNode->number.number = num;
	newNode->next = NULL;
	return newNode;
}

void listAppend(List *list, int origin, int long num) {
	int flag = 0;
	if (list->head == NULL) {
		listNode* newNode = listNodeCreate(origin, num);
		list->head = newNode;
	}else{
		listNode *tmp = list->head;
		listNode *tmpPrev = tmp;
		while(tmp != NULL){
			tmpPrev = tmp;
			if (tmp->number.origin == origin)
			{
				if (tmp->number.number == num)
				{
					flag++;
					break;	
				}
			}
			tmp = tmp->next;
		}
		if (!flag)
		{
			listNode *newNode = listNodeCreate(origin, num);
			tmpPrev->next = newNode;
		}
	}
	return;
}

void listDestroy(List *list) {
	listNode* tmp = list->head;
	while (tmp != NULL) {
		listNode* tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	free(list);
}

void findContacts1(List *L, Bucket *tmpNumBucket, int numPosition){
	int i;
	if (numPosition >= 0)
	{
		CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
		while(tmpRecBucket != NULL){
			for ( i = 0; i < tmpRecBucket->maxRecords; ++i)
			{
				if (tmpRecBucket->records[i] != NULL)
				{
					listAppend(L,tmpRecBucket->records[i]->calleeOrigin, tmpRecBucket->records[i]->calleeNum);
				}
			}
			tmpRecBucket = tmpRecBucket->next;
		}
	}
}

void findContacts2(List *L, Bucket *tmpNumBucket, int numPosition){
	int i;
	if (numPosition >= 0)
	{
		CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
		while(tmpRecBucket != NULL){
			for ( i = 0; i < tmpRecBucket->maxRecords; ++i)
			{
				if (tmpRecBucket->records[i] != NULL)
				{
					listAppend(L,tmpRecBucket->records[i]->callerOrigin, tmpRecBucket->records[i]->callerNum);
				}
			}
			tmpRecBucket = tmpRecBucket->next;
		}
	}
}

void mergeLists(List *L1, List *L2, List *mergedList){
	listNode *tmp1 = L1->head;
	listNode *tmp2 = L2->head;
	int flag = 0;
	while(tmp1 != NULL){
		tmp2 = L2->head;
		while(tmp2 != NULL){
			if (tmp1->number.origin == tmp2->number.origin)
			{
				if (tmp1->number.number == tmp2->number.number)
				{
					flag++;
					break;	
				}
			}
			tmp2 = tmp2->next;
		}
		if (flag)
		{
			listAppend(mergedList,tmp1->number.origin, tmp1->number.number);
			flag = 0;
		}
		tmp1 = tmp1->next;
	}
}

int notContacted(List *L1, List *L2){
	listNode *tmp1 = L1->head;
	listNode *tmp2 = L2->head;
	while(tmp1 != NULL){
		tmp2 = L2->head;
		while(tmp2 != NULL){
			if (tmp1->number.origin == tmp2->number.origin)
			{
				if (tmp1->number.number == tmp2->number.number)
				{
					return 0;
				}
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	return 1;
}