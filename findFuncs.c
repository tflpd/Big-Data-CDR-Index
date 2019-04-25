#include "findFuncs.h"

unsigned long hashFunc(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c;

return hash;
}

Bucket *findNumber(Bucket *bucket, char *num, int *pos){
	int i;
	*pos = -1;
	Bucket *tmpBucket = bucket;
	while(bucket != NULL){
		for (i = 0; i < bucket->curNumbers + 1; ++i)
		{
			if(!strcmp(bucket->numbers[i]->number, num)){
				*pos = i;
				break;
			}
		}
		if (*pos != -1)
		{
			break;
		}
		tmpBucket = bucket;
		bucket = bucket->next;
	}
	if (*pos == -1)
	{
		bucket = tmpBucket;
	}
	return bucket;
}

CDRBucket *findRecord(CDRBucket *bucket, char *id, int *pos){
	int i;
	*pos = -1;
	CDRBucket *tmpBucket = bucket;
	while(bucket != NULL){
		for (i = 0; i < bucket->maxRecords; ++i)
		{
			if (bucket->records[i] != NULL)
			{
				if(!strcmp(bucket->records[i]->id, id)){
					*pos = i;
					break;
				}
			}
		}
		if (*pos != -1)
		{
			break;
		}
		tmpBucket = bucket;
		bucket = bucket->next;
	}
	if (*pos == -1)
	{
		bucket = tmpBucket;
	}
	return bucket;
}