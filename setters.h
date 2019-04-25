#ifndef SETTERS
#define SETTERS

#include <stdlib.h>
#include <string.h>
#include "hashStructs.h"

/*Sets the values of record tmpStruct to a new allocated CDR and returns a pointer to it*/
CDR *recordSetter(CDR *tmpStruct);

/*Creating and initializing a new number bucket*/
void numBucketInit(Bucket *tmpNumBucket, int bucketSize);

/*Creating and initializing a new record bucket*/
void CDRBucketInit(CDRBucket *tmpRecBucket, int bucketSize);

#endif