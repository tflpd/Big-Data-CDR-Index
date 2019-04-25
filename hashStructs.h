#ifndef HASHSTRUCTS
#define HASHSTRUCTS

typedef struct cdr
{
	char *id;
	int callerOrigin;
	long int callerNum;
	int calleeOrigin;
	long int calleeNum;
	long int day;	//days months and years counted all as an amount of days
	int min;	//minutes and hours also
	int duration;
	int type;
	int tarrif;
	long int fault;
} CDR;

typedef struct CDRBucket
{
	CDR **records;
	int curRecords;
	int maxRecords;
	struct CDRBucket *next;
} CDRBucket;

typedef struct numbernode
{
	char *number;
	CDRBucket *calls;
} numberNode;

typedef struct Bucket
{
	numberNode **numbers;
	int curNumbers;
	int maxNumbers;
	struct Bucket *next;
} Bucket;

#endif