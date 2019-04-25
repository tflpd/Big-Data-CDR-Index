#include "setters.h"

CDR *recordSetter(CDR *tmpStruct){

	CDR *tmpCDR = realloc(NULL, sizeof(CDR));
	tmpCDR->id = realloc(NULL, sizeof(char)*strlen(tmpStruct->id) + 1);
	strcpy(tmpCDR->id, tmpStruct->id);
	
	tmpCDR->callerOrigin = tmpStruct->callerOrigin;
	tmpCDR->callerNum = tmpStruct->callerNum;
	tmpCDR->calleeOrigin = tmpStruct->calleeOrigin;
	tmpCDR->calleeNum = tmpStruct->calleeNum;
	tmpCDR->day = tmpStruct->day;
	tmpCDR->min = tmpStruct->min;
	tmpCDR->duration = tmpStruct->duration;
	tmpCDR->type = tmpStruct->type;
	tmpCDR->tarrif = tmpStruct->tarrif;
	tmpCDR->fault = tmpStruct->fault;
	return tmpCDR;
}

void numBucketInit(Bucket *tmpNumBucket, int bucketSize){
	tmpNumBucket->numbers = realloc(NULL, sizeof(numberNode *)*bucketSize);
	tmpNumBucket->curNumbers = -1;
	tmpNumBucket->maxNumbers = bucketSize;
	tmpNumBucket->next = NULL;
}

void CDRBucketInit(CDRBucket *tmpRecBucket, int bucketSize){
	int i;

	tmpRecBucket->records = realloc(NULL, sizeof(CDR *)*bucketSize);
	for (i = 0; i < bucketSize; ++i)
	{
		tmpRecBucket->records[i] = NULL;
	}
	tmpRecBucket->curRecords = -1;
	tmpRecBucket->maxRecords = bucketSize;
	tmpRecBucket->next = NULL;
}