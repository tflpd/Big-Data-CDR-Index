#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashStructs.h"
#include "stringManipulate.h"
#include "list.h"
#include "findFuncs.h"
#include "utilities.h"

int main(int argc, char const *argv[])
{
	if (argc != 9 && argc != 7)
	{
		printf("Wrong number of arguments.\n");
		printf("Correct use is:\n");
		printf("./werhauz -o Operations -h1 Hashtable1NumOfEntries -h2 Hashtable2NumOfEntries -s BucketSize\nOr:\n");
		printf("./werhauz -h1 Hashtable1NumOfEntries -h2 Hashtable2NumOfEntries -s BucketSize\n");
		exit(0);
	}

	int i, inputPos = 0;
	FILE *filepointerIn = NULL;
	int instrCounter = 0, instrSize = 10, callerHashEntries, calleeHashEntries, bucketBytes = -1, bucketSize = -1;
	char **buf = realloc(NULL, sizeof(char *)*instrSize);

	for (i = 1; i < argc; ++i)
	{
		if (!strcmp(argv[i],"-o"))
		{
			filepointerIn = fopen (argv[i + 1],"r");
			inputPos=i + 1;
			if (filepointerIn == NULL)
			{
				printf("Unable to open input file.\n");
				free(buf);
				exit(1);
			}
			while(!feof(filepointerIn)){	//Inserting to array buff all the instructions given from operations file
				buf[instrCounter] = inputString(filepointerIn, 74);
				if (!strlen(buf[instrCounter]))
				{
					free(buf[instrCounter]);
					continue;
				}
				instrCounter++;
				if (instrCounter == instrSize)
				{
					buf = realloc(buf, sizeof(char *)*(instrSize+=256));
				}
			}
			buf = realloc(buf, sizeof(char *)*(instrCounter));
			
		}else if (!strcmp(argv[i],"-h1"))
		{
			callerHashEntries = atoi(argv[i + 1]);
		}else if (!strcmp(argv[i],"-h2"))
		{
			calleeHashEntries = atoi(argv[i + 1]);
		}else if (!strcmp(argv[i],"-s"))
		{
			bucketBytes = atoi(argv[i + 1]);
			bucketSize = bucketBytes / sizeof(numberNode);
		}
	}

	if (bucketSize == -1)
	{
		printf("Bucket size has to be given.\n");
		exit(2);
	}

	Bucket **hashTable1 = realloc(NULL, sizeof(Bucket *)*callerHashEntries);
	for (i = 0; i < callerHashEntries; ++i)
	{
		hashTable1[i] = realloc(NULL, sizeof(Bucket));
		hashTable1[i]->numbers = realloc(NULL, sizeof(numberNode *)*bucketSize);
		hashTable1[i]->curNumbers = -1;
		hashTable1[i]->maxNumbers = bucketSize;
		hashTable1[i]->next = NULL;
	}

	Bucket **hashTable2 = realloc(NULL, sizeof(Bucket *)*calleeHashEntries);
	for (i = 0; i < calleeHashEntries; ++i)
	{
		hashTable2[i] = realloc(NULL, sizeof(Bucket));
		hashTable2[i]->numbers = realloc(NULL, sizeof(numberNode *)*bucketSize);
		hashTable2[i]->curNumbers = -1;
		hashTable2[i]->maxNumbers = bucketSize;
		hashTable2[i]->next = NULL;
	}

	unsigned long hashKey1 = 0;
	unsigned long hashKey2 = 0;

	int tmpInputCounter = instrCounter;


	CDR *tmpStruct = realloc(NULL, sizeof(CDR));
	char *instruction;
	while(1){
		if (tmpInputCounter)	//if there are still operations in the operation file to execute
		{
			instruction = realloc(NULL, sizeof(char)*(strlen(buf[instrCounter - tmpInputCounter]) + 1));
			strcpy(instruction, buf[instrCounter - tmpInputCounter]);
		}else{	//else take instructions from the command line
			printf("Input from input file ended.\n");
			printf("Give an instruction:\n");
			instruction = inputString(stdin, 74);
		}
		char *instr;
		char *instr2;
		char *callerStr;
		char *callerInt;
		char *calleeStr;
		char *calleeInt;
		instr = strtok(instruction, " ");
		if (!strcmp(instr, "insert"))
		{
			instr2 = strtok(NULL, ";");
			tmpStruct->id = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
			strcpy(tmpStruct->id, instr2);

			instr2 = strtok(NULL, ";");
			callerStr = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
			strcpy(callerStr,instr2);
			callerInt = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
			strcpy(callerInt,instr2);

			instr2 = strtok(NULL, ";");
			calleeStr = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
			strcpy(calleeStr,instr2);
			calleeInt = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
			strcpy(calleeInt,instr2);

			hashKey1 = hashFunc(callerStr) % callerHashEntries;
			hashKey2 = hashFunc(calleeStr) % calleeHashEntries;
			//hashKey1 = 0;

			/*Seperating the instruction to absorb each tokken*/
			instr2 = strtok(NULL, ";");
			tmpStruct->day = (strtol(instr2, NULL, 10) / 1000000);
			tmpStruct->day += ((((strtol(instr2, NULL, 10) / 10000) % 100) - 1) * 30);
			tmpStruct->day += (((strtol(instr2, NULL, 10) % 10000) - 1) * 365);
			instr2 = strtok(NULL, ":");
			tmpStruct->min = (atoi(instr2) * 60);
			instr2 = strtok(NULL, ";");
			tmpStruct->min += atoi(instr2);
			instr2 = strtok(NULL, ";");
			tmpStruct->duration = atoi(instr2);
			instr2 = strtok(NULL, ";");
			tmpStruct->type = atoi(instr2);
			instr2 = strtok(NULL, ";");
			tmpStruct->tarrif = atoi(instr2);
			instr2 = strtok(NULL, "\n");
			tmpStruct->fault = strtol(instr2, NULL, 10);

			instr2 = strtok(callerInt,"-");
			tmpStruct->callerOrigin = atoi(instr2);
			instr2 = strtok(NULL,"\n");
			tmpStruct->callerNum = strtol(instr2, NULL, 10);


			instr2 = strtok(calleeInt,"-");
			tmpStruct->calleeOrigin = atoi(instr2);
			instr2 = strtok(NULL,"\n");
			tmpStruct->calleeNum = strtol(instr2, NULL, 10);

			if ((tmpStruct->fault / 100) != 2)	//ifthere is a fault on the cdr dont inserted as instructed from piazza
			{									// it can be skipped if wanted
					free(tmpStruct->id);
					free(callerStr);
					free(callerInt);
					free(calleeStr);
					free(calleeInt);
					free(instruction);
					tmpInputCounter--;
					continue;
			}	

			printf("insert >>>>\n");

			////////////////////////////////Inserting to hashtable1, the caller table////////////////////////////

			Bucket *tmpNumBucket = hashTable2[hashKey2];
			int numPosition = -1;
			int *numPositionP = &numPosition;
			tmpNumBucket = findNumber(hashTable2[hashKey2], calleeStr, numPositionP);	// trying to find the number and if found
			numPosition = *numPositionP;												// a pointer (tmpNumBucket) to its bucket is returned and
																						// its position in the bucket (numPosition) also
			if (numPosition < 0)														// if not found num position will be negative so it has to
			{																			// be inserted in the structs
				if (tmpNumBucket->curNumbers + 1 == tmpNumBucket->maxNumbers)			// if the bucket to be inserted is full overflow bucket will be
				{																		// allocated
					tmpNumBucket->next = realloc(NULL, sizeof(Bucket));
					tmpNumBucket = tmpNumBucket->next;
					numBucketInit(tmpNumBucket, bucketSize);
				}

				
				tmpNumBucket->curNumbers++;
				tmpNumBucket->numbers[tmpNumBucket->curNumbers] = realloc(NULL, sizeof(numberNode));
				
				tmpNumBucket->numbers[tmpNumBucket->curNumbers]->number = realloc(NULL, sizeof(char *)*strlen(calleeStr) + 1);
				strcpy(tmpNumBucket->numbers[tmpNumBucket->curNumbers]->number, calleeStr);
				
				tmpNumBucket->numbers[tmpNumBucket->curNumbers]->calls = realloc(NULL, sizeof(CDRBucket));
				CDRBucketInit(tmpNumBucket->numbers[tmpNumBucket->curNumbers]->calls, bucketSize);
				numPosition = tmpNumBucket->curNumbers;
			}

			CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
			while(tmpRecBucket->next != NULL){
				tmpRecBucket = tmpRecBucket->next;
			}

			if ((tmpRecBucket->curRecords + 1) == tmpRecBucket->maxRecords)
			{
				tmpRecBucket->next = realloc(NULL, sizeof(CDRBucket));
				tmpRecBucket = tmpRecBucket->next;
				CDRBucketInit(tmpRecBucket, bucketSize);
			}

			tmpRecBucket->curRecords++;
			int recordPosition = tmpRecBucket->curRecords;

			tmpRecBucket->records[recordPosition] = recordSetter(tmpStruct);

			CDR *CDRP = tmpRecBucket->records[recordPosition];

			////////////////////////////////Now inserting to hashtable2, the callee table////////////////////////////
			tmpNumBucket = hashTable1[hashKey1];
			numPosition = -1;
			tmpNumBucket = findNumber(hashTable1[hashKey1], callerStr, numPositionP);
			numPosition = *numPositionP;
			
			if (numPosition < 0)
			{
				if (tmpNumBucket->curNumbers + 1 == tmpNumBucket->maxNumbers)
				{
					tmpNumBucket->next = realloc(NULL, sizeof(Bucket));
					tmpNumBucket = tmpNumBucket->next;
					numBucketInit(tmpNumBucket, bucketSize);
				}

				
				tmpNumBucket->curNumbers++;
				tmpNumBucket->numbers[tmpNumBucket->curNumbers] = realloc(NULL, sizeof(numberNode));
				
				tmpNumBucket->numbers[tmpNumBucket->curNumbers]->number = realloc(NULL, sizeof(char *)*strlen(callerStr) + 1);
				strcpy(tmpNumBucket->numbers[tmpNumBucket->curNumbers]->number, callerStr);
				
				tmpNumBucket->numbers[tmpNumBucket->curNumbers]->calls = realloc(NULL, sizeof(CDRBucket));
				CDRBucketInit(tmpNumBucket->numbers[tmpNumBucket->curNumbers]->calls, bucketSize);
				numPosition = tmpNumBucket->curNumbers;
			}

			tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
			while(tmpRecBucket->next != NULL){
				tmpRecBucket = tmpRecBucket->next;
			}

			if ((tmpRecBucket->curRecords + 1) == tmpRecBucket->maxRecords)
			{
				tmpRecBucket->next = realloc(NULL, sizeof(CDRBucket));
				tmpRecBucket = tmpRecBucket->next;
				CDRBucketInit(tmpRecBucket, bucketSize);
			}

			tmpRecBucket->curRecords++;
			recordPosition = tmpRecBucket->curRecords;

			tmpRecBucket->records[recordPosition] = CDRP;
			///////////////////////////////////////////////////////////////////////////////////////////////////////

			free(tmpStruct->id);
			free(callerStr);
			free(callerInt);
			free(calleeStr);
			free(calleeInt);
		}else if (!strcmp(instr, "print"))
		{
			instr2 = strtok(NULL, "\n");
			if (!strcmp(instr2, "hashtable2"))
			{
				printHashT(hashTable2, calleeHashEntries);
			}else if (!strcmp(instr2, "hashtable1"))
			{
				printHashT(hashTable1, callerHashEntries);
			}
		}else if (!strcmp(instr, "delete"))
		{
			instr2 = strtok(NULL, " ");
			char *callerStr = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
			strcpy(callerStr, instr2);

			instr2 = strtok(NULL, "\n");
			printf("delete >>>>\n");
			hashKey1 = hashFunc(callerStr) % callerHashEntries;
			Bucket *tmpNumBucket = hashTable1[hashKey1];
			int numPosition = -1;
			int *numPositionP = &numPosition;
			int recPosition = -1;
			int *recPositionP = &recPosition;
			tmpNumBucket = findNumber(hashTable1[hashKey1], callerStr, numPositionP);
			numPosition = *numPositionP;
			if(numPosition < 0){
				printf("\t");
				printf("DError.\n");
			}else{
				CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
				tmpRecBucket = findRecord(tmpNumBucket->numbers[numPosition]->calls, instr2, recPositionP);
				recPosition = *recPositionP;
				if (recPosition < 0)
				{
					printf("\t");
					printf("DError.\n");
				}else{
					tmpRecBucket->records[recPosition] = NULL;
					printf("\t");
					printf("Deleted %s.\n", instr2);
				}
			}
			free(callerStr);
		}else if (!strcmp(instr, "find"))
		{
			printf("find >>>>\n");
			instr2 = strtok(NULL, " ");
			char *callerStr = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
			strcpy(callerStr,instr2);
			char **args = realloc(NULL, sizeof(char *)*4);
			for (i = 0; i < 4; ++i)
			{
				args[i] = NULL;
			}
			int argCounter = 0;
			while(1){		//parsing the arguments of find and saving them to array args
				instr2 = strtok(NULL, " ");
				if (instr2 == NULL)
				{
					break;
				}
				args[argCounter] = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
				strcpy(args[argCounter], instr2);
				argCounter++;
			}
			
			hashKey1 = hashFunc(callerStr) % callerHashEntries;
			Bucket *tmpNumBucket = hashTable1[hashKey1];
			int numPosition = -1;
			int *numPositionP = &numPosition;
			tmpNumBucket = findNumber(hashTable1[hashKey1], callerStr, numPositionP);
			numPosition = *numPositionP;


			find(argCounter, args, tmpNumBucket, numPosition);

			for (i = 0; i < argCounter; ++i)
			{
				free(args[i]);
			}
			free(args);
			free(callerStr);
		}
		else if (!strcmp(instr, "lookup"))
		{
			printf("lookup >>>>\n");
			instr2 = strtok(NULL, " ");
			char *calleeStr = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
			strcpy(calleeStr,instr2);
			char **args = realloc(NULL, sizeof(char *)*4);
			for (i = 0; i < 4; ++i)
			{
				args[i] = NULL;
			}
			int argCounter = 0;
			while(1){
				instr2 = strtok(NULL, " ");
				if (instr2 == NULL)
				{
					break;
				}
				args[argCounter] = realloc(NULL, sizeof(char)*strlen(instr2) + 1);
				strcpy(args[argCounter], instr2);
				argCounter++;
			}
			
			hashKey2 = hashFunc(calleeStr) % calleeHashEntries;
			Bucket *tmpNumBucket = hashTable2[hashKey2];
			int numPosition = -1;
			int *numPositionP = &numPosition;
			tmpNumBucket = findNumber(hashTable2[hashKey2], calleeStr, numPositionP);
			numPosition = *numPositionP;

			find(argCounter, args, tmpNumBucket, numPosition);
			
			for (i = 0; i < argCounter; ++i)
			{
				free(args[i]);
			}
			free(args);
			free(calleeStr);
		}else if (!strcmp(instr, "topdest"))
		{
			char *callerStr = strtok(NULL, " ");

			hashKey1 = hashFunc(callerStr) % callerHashEntries;
			Bucket *tmpNumBucket = hashTable1[hashKey1];
			int numPosition = -1;
			int *numPositionP = &numPosition;
			tmpNumBucket = findNumber(hashTable1[hashKey1], callerStr, numPositionP);
			numPosition = *numPositionP;
			printf("topdest >>>>\n");
			if (numPosition < 0)
			{
				printf("\t");
				printf("No calls found.\n");
			}else{
				topDest(tmpNumBucket, numPosition);
			}

		}else if (!strcmp(instr, "indist"))
		{
			char *num1 = strtok(NULL, " ");
			char *num2 = strtok(NULL, " ");

			printf("indist >>>>\n");

			indist(num1, num2, hashTable1, hashTable2, callerHashEntries, calleeHashEntries);
		}else if (!strcmp(instr, "bye"))
		{	
			printf("bye >>>>\n");
			freeMemory(0, hashTable1, hashTable2, callerHashEntries, calleeHashEntries);
			for (i = 0; i < callerHashEntries; ++i)
			{
				hashTable1[i] = realloc(NULL, sizeof(Bucket));
				hashTable1[i]->numbers = realloc(NULL, sizeof(numberNode *)*bucketSize);
				hashTable1[i]->curNumbers = -1;
				hashTable1[i]->maxNumbers = bucketSize;
				hashTable1[i]->next = NULL;
			}

			for (i = 0; i < calleeHashEntries; ++i)
			{
				hashTable2[i] = realloc(NULL, sizeof(Bucket));
				hashTable2[i]->numbers = realloc(NULL, sizeof(numberNode *)*bucketSize);
				hashTable2[i]->curNumbers = -1;
				hashTable2[i]->maxNumbers = bucketSize;
				hashTable2[i]->next = NULL;
			}
		}else if (!strcmp(instr, "dump"))
		{
			char *hashT = strtok(NULL, " ");
			printf("dump >>>>\n");
			if (!strcmp(hashT,"hashtable1"))
			{
				FILE *fp = fopen("dumpedHashT1.txt", "w");
				dumpHashT(hashTable1, callerHashEntries, fp);
				fclose(fp);
			}else if (!strcmp(hashT,"hashtable2"))
			{
				FILE *fp = fopen("dumpedHashT2.txt", "w");
				dumpHashT(hashTable2, calleeHashEntries, fp);
				fclose(fp);
			}
		}else if (!strcmp(instr, "exit"))
		{
			free(instruction);
			break;
		}else{
			printf("Unknown command given from input file.\n");
		}
		free(instruction);
		if (tmpInputCounter)	//if just read instruction from input file subtract one from the instructions counter
		{
			tmpInputCounter--;
		}
	}
	free(tmpStruct);
	
	freeMemory(1, hashTable1, hashTable2, callerHashEntries, calleeHashEntries);

	if (instrCounter)	//if there was an input file free the array keeping the instructions and close th file pointer
	{
		for (i = 0; i < instrCounter ; ++i)
		{
			free(buf[i]);
		}
		fclose(filepointerIn);
	}
	free(buf);

	return 0;
}