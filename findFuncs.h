#ifndef FINDFUNCS
#define FINDFUNCS

#include <string.h>
#include "hashStructs.h"

/*Hash function for strings*/
unsigned long hashFunc(unsigned char *str);

/*Function to locate (if exists) a number and its position in its number bucket*/
Bucket *findNumber(Bucket *bucket, char *num, int *pos);

/*Function to locate and (if exists) a record id and its position in its record bucket*/
CDRBucket *findRecord(CDRBucket *bucket, char *id, int *pos);

#endif