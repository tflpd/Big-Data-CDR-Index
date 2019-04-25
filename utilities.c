#include "utilities.h"

void printHashT(Bucket **hashTable, int entries){
	int i, j, k;
	for (i = 0; i < entries; ++i)
	{
		Bucket *tmpNumBucket = hashTable[i];
		do{

			for (j = 0; j < tmpNumBucket->curNumbers + 1; ++j)
			{
				CDRBucket *tmpRecBucket = tmpNumBucket->numbers[j]->calls;
				printf("Number %s includes the following CDR's :\n", tmpNumBucket->numbers[j]->number);
				do{

					for (k = 0; k < tmpRecBucket->maxRecords; ++k)
					{
						if (tmpRecBucket->records[k] != NULL)
						{
							//printf("\t");
							printCDR(*tmpRecBucket->records[k]);
						}
					}

					tmpRecBucket = tmpRecBucket->next;
				}while(tmpRecBucket != NULL);
			}

			tmpNumBucket = tmpNumBucket->next;
		}while(tmpNumBucket != NULL);
			
	}
}

void dumpHashT(Bucket **hashTable, int entries, FILE *fp){
	int i, j, k;
	for (i = 0; i < entries; ++i)
	{
		Bucket *tmpNumBucket = hashTable[i];
		do{

			for (j = 0; j < tmpNumBucket->curNumbers + 1; ++j)
			{
				CDRBucket *tmpRecBucket = tmpNumBucket->numbers[j]->calls;
				//printf("Number %s includes the following CDR's :\n", tmpNumBucket->numbers[j]->number);
				do{

					for (k = 0; k < tmpRecBucket->maxRecords; ++k)
					{
						if (tmpRecBucket->records[k] != NULL)
						{
							//printf("\t");
							printFileCDR(fp, *tmpRecBucket->records[k]);
						}
					}

					tmpRecBucket = tmpRecBucket->next;
				}while(tmpRecBucket != NULL);
			}

			tmpNumBucket = tmpNumBucket->next;
		}while(tmpNumBucket != NULL);
			
	}
}


void find(int argCounter, char **args, Bucket *tmpNumBucket, int numPosition){
	int i, printFlag = 0;
	
	if (argCounter == 0)	// find is accepted only if it has 0, 2 ([time1][time2]), 4 ([time1][year1][year2][time2]) arguments
	{
		if(numPosition >= 0){
			CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
			while(tmpRecBucket != NULL){
				for ( i = 0; i < tmpRecBucket->maxRecords; ++i)
				{
					if (tmpRecBucket->records[i] != NULL)
					{
						printCDR(*tmpRecBucket->records[i]);
						printFlag = 1;
					}
				}
				tmpRecBucket = tmpRecBucket->next;
			}
		}	
	}else if (argCounter == 2)
	{
		if(numPosition >= 0){
			int min1;
			int min2;
			char *check;
			min1 = (atoi(strtok(args[0], ":")) * 60);
			check = strtok(NULL, " ");
			if (check != NULL)
			{
				min1 += atoi(check);
				min2 = (atoi(strtok(args[1], ":")) * 60);
				min2 += atoi(strtok(NULL, " "));
				int flag = 0;
				if (min1 > min2)
				{
					flag++;
				}
				CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
				while(tmpRecBucket != NULL){
					for ( i = 0; i < tmpRecBucket->maxRecords; ++i)
					{
						if (tmpRecBucket->records[i] != NULL)
						{
							int min = tmpRecBucket->records[i]->min;
							if (!flag)
							{
								if ((min >= min1) && (min <= min2))
								{
									printCDR(*tmpRecBucket->records[i]);
									printFlag = 1;
								}
							}else{
								if ((min >= min1) || (min <= min2))
								{
									printCDR(*tmpRecBucket->records[i]);
									printFlag = 1;
								}
							}
						}
					}
					tmpRecBucket = tmpRecBucket->next;
				}
			}else{
				long int day1;
				long int day2;
				check = strtok(args[0], " ");
				day1 = (strtol(check, NULL, 10)  / 1000000);
				day1 += ((((strtol(check, NULL, 10)  / 1000000) % 100) - 1) * 30);
				day1 += (((strtol(check, NULL, 10) % 10000) - 1) * 365);

				check = strtok(args[1], " ");
				day2 = (strtol(check, NULL, 10)  / 1000000);
				day2 += ((((strtol(check, NULL, 10)  / 1000000) % 100) - 1) * 30);
				day2 += (((strtol(check, NULL, 10) % 10000) - 1) * 365);

				if (day1 > day2)
				{
					printf("\t");
					printf("Date 1 has to be earlier than Date 2.\n");
					return;
				}

				CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
				while(tmpRecBucket != NULL){
					for ( i = 0; i < tmpRecBucket->maxRecords; ++i)
					{
						if (tmpRecBucket->records[i] != NULL)
						{
							long int day = tmpRecBucket->records[i]->day;
							
							if ((day >= day1) && (day <= day2))
							{
								printCDR(*tmpRecBucket->records[i]);
								printFlag = 1;
							}
						}
					}
					tmpRecBucket = tmpRecBucket->next;
				}
			}
		}

	}else if (argCounter == 4)
	{
		int min1,min2,flag = 0;
		long int day1,day2;
		char *check;
		min1 = (atoi(strtok(args[0], ":")) * 60);
		min1 += atoi(strtok(NULL, " "));
		check = strtok(args[1], " ");
		day1 = (strtol(check, NULL, 10)  / 1000000);
		day1 += ((((strtol(check, NULL, 10)  / 10000) % 100) - 1) * 30);
		day1 += (((strtol(check, NULL, 10) % 10000) - 1) * 365);

		min2 = (atoi(strtok(args[2], ":")) * 60);
		min2 += atoi(strtok(NULL, " "));
		check = strtok(args[3], " ");
		day2 = (strtol(check, NULL, 10)  / 1000000);
		day2 += ((((strtol(check, NULL, 10)  / 10000) % 100) - 1) * 30);
		day2 += (((strtol(check, NULL, 10) % 10000) - 1) * 365);

		if (min1 > min2)
		{
			flag++;
		}

		if (day1 > day2)
		{
			printf("\t");
			printf("Date 1 has to be earlier than Date 2.\n");
			return;
		}

		if (numPosition >= 0)
		{
			CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
			while(tmpRecBucket != NULL){
				for ( i = 0; i < tmpRecBucket->maxRecords; ++i)
				{
					if (tmpRecBucket->records[i] != NULL)
					{
						long int day = tmpRecBucket->records[i]->day;
						if ((day >= day1) && (day <= day2))
						{
							int min = tmpRecBucket->records[i]->min;
							if (!flag)
							{
								if ((min >= min1) && (min <= min2))
								{
									printCDR(*tmpRecBucket->records[i]);
									printFlag = 1;
								}
							}else{
								if ((min >= min1) || (min <= min2))
								{
									printCDR(*tmpRecBucket->records[i]);
									printFlag = 1;
								}
							}
						}
					}
				}
				tmpRecBucket = tmpRecBucket->next;
			}
		}
	}else{
		printf("\t");
		printf("Wrong number of arguments at find.\n");
	}
	if (!printFlag)
	{
		printf("\t");
		printf("No CDRs found.\n");
	}
}

void topDest(Bucket *tmpNumBucket, int numPosition){
	int flag, counter, i, j, position, size = tmpNumBucket->maxNumbers*2, max;
	position = 0;
	flag = 0;
	counter = 0;
	max = 0;

	int *numbers = realloc(NULL, sizeof(int)*(tmpNumBucket->maxNumbers*2));
	int *counters = realloc(NULL, sizeof(int)*(tmpNumBucket->maxNumbers*2));
	for (i = 0; i < size; ++i)
	{
		numbers[i] = -1;	//two parallel arrays, one for each counter code
		counters[i] = 0;	//and one for the times this code had been callled
	}

	CDRBucket *tmpRecBucket = tmpNumBucket->numbers[numPosition]->calls;
	while(tmpRecBucket != NULL){
		for ( i = 0; i < tmpRecBucket->maxRecords; ++i)
		{
			if (tmpRecBucket->records[i] != NULL)
			{
				position = 0;
				while(position < size){
					if (tmpRecBucket->records[i]->calleeOrigin == numbers[position])	//if the country code exists
					{
						counters[position]++;	//update its score
						if (counters[position] > max)
						{
							max = counters[position];	//and if is the new max keep him
						}
						flag++;
						break;
					}
					position++;
				}
				if (!flag)	//if code wasnt found add him on the array
				{
					numbers[counter] = tmpRecBucket->records[i]->calleeOrigin;
					counters[counter] = 1;
					if (counters[counter] > max)
						{
							max = counters[counter];
						}
					counter++;
					if (counter == size)	//if the array size reached the allocated size realloc
					{
						size *= 2;
						numbers = realloc(numbers, sizeof(int)*(size));
						counters = realloc(counters, sizeof(int)*(size));
						for (j = counter; j < size; ++j)
						{
							numbers[j] = -1;
							counters[i] = 0;
						}
					}
				}
			}
		}
		tmpRecBucket = tmpRecBucket->next;
	}
	for (i = 0; i < counter; ++i) //print all the codes equal to max
	{
		if (counters[i] == max)
		{
			printf("\tCountry Code: %d, Calls made %d.\n", numbers[i], counters[i]);
		}
	}
	if (!counter)
	{
		printf("\t");
		printf("No calls found.\n");
	}
	free(numbers);
	free(counters);
}


void indist(char *num1, char *num2, Bucket **hashTable1, Bucket **hashTable2, int callerHashEntries, int calleeHashEntries){

	int hashKey1 = hashFunc(num1) % callerHashEntries;

	Bucket *tmpNumBucket = hashTable1[hashKey1];
	int i, numPosition = -1;
	int *numPositionP = &numPosition;
	tmpNumBucket = findNumber(hashTable1[hashKey1], num1, numPositionP);
	numPosition = *numPositionP;

	/////////////////////////Create a list with all the numbers num1 has contacted/////////////////////
	List *L1 = listCreate();

	//finds all the contacts from the caller side
	findContacts1(L1, tmpNumBucket, numPosition);

	int hashKey2 = hashFunc(num1) % calleeHashEntries;

	tmpNumBucket = hashTable2[hashKey2];
	numPosition = -1;
	numPositionP = &numPosition;
	tmpNumBucket = findNumber(hashTable2[hashKey2], num1, numPositionP);
	numPosition = *numPositionP;

	//append to the already existing list all the contacts from callee side
	findContacts2(L1, tmpNumBucket, numPosition);



	hashKey1 = hashFunc(num2) % callerHashEntries;

	tmpNumBucket = hashTable1[hashKey1];
	numPosition = -1;
	numPositionP = &numPosition;
	tmpNumBucket = findNumber(hashTable1[hashKey1], num2, numPositionP);
	numPosition = *numPositionP;

	/////////////////////////Create a list with all the numbers num2 has contacted/////////////////////
	List *L2 = listCreate();

	//finds all the contacts from the caller side
	findContacts1(L2, tmpNumBucket, numPosition);

	hashKey2 = hashFunc(num2) % calleeHashEntries;

	tmpNumBucket = hashTable2[hashKey2];
	numPosition = -1;
	numPositionP = &numPosition;
	tmpNumBucket = findNumber(hashTable2[hashKey2], num2, numPositionP);
	numPosition = *numPositionP;

	//append to the already existing list all the contacts from callee side
	findContacts2(L2, tmpNumBucket, numPosition);


	char buffer[50];
	List *mergedList = listCreate();

	//Find the intersection of L1 and L2
	mergeLists(L1, L2, mergedList);
	listNode *tmp = mergedList->head;
	int foundIndist = 0;

	while(tmp != NULL){
		sprintf(buffer, "%03d-%010ld", tmp->number.origin, tmp->number.number);
		//Create a list for every node in the intersection and find its contacts
		List *tmpList = listCreate();

		hashKey1 = hashFunc(buffer) % callerHashEntries;

		tmpNumBucket = hashTable1[hashKey1];
		numPosition = -1;
		numPositionP = &numPosition;
		tmpNumBucket = findNumber(hashTable1[hashKey1], buffer, numPositionP);
		numPosition = *numPositionP;

		findContacts1(tmpList, tmpNumBucket, numPosition);

		hashKey2 = hashFunc(buffer) % calleeHashEntries;

		tmpNumBucket = hashTable2[hashKey2];
		numPosition = -1;
		numPositionP = &numPosition;
		tmpNumBucket = findNumber(hashTable2[hashKey2], buffer, numPositionP);
		numPosition = *numPositionP;

		findContacts2(tmpList, tmpNumBucket, numPosition);

		//if in his contact is not any node of the list then print this num
		if(notContacted(tmpList, mergedList)){
			printf("\t");
			printf("%03d-%010ld\n", tmp->number.origin, tmp->number.number);
			foundIndist++;
		}

		listDestroy(tmpList);

		tmp = tmp->next;
	}
	if (!foundIndist)
	{
		printf("\t");
		printf("No indist found\n");
	}

	listDestroy(mergedList);

	listDestroy(L1);
	listDestroy(L2);
}

void freeMemory(int mode, Bucket **hashTable1, Bucket **hashTable2, int callerHashEntries, int calleeHashEntries){
	int j, k, i;

	for (i = 0; i < callerHashEntries; ++i)
	{
		do{
			Bucket *tmpNumBucket = hashTable1[i]->next;

			for (j = 0; j < hashTable1[i]->curNumbers + 1; ++j)
			{
				do{
					CDRBucket *tmpRecBucket = hashTable1[i]->numbers[j]->calls->next;

					for (k = 0; k < hashTable1[i]->numbers[j]->calls->maxRecords; ++k)
					{
						if (hashTable1[i]->numbers[j]->calls->records[k] != NULL)
						{
							hashTable1[i]->numbers[j]->calls->records[k] = NULL;	
						}
					}
					free(hashTable1[i]->numbers[j]->calls->records);
					free(hashTable1[i]->numbers[j]->calls);

					hashTable1[i]->numbers[j]->calls = tmpRecBucket;
				}while(hashTable1[i]->numbers[j]->calls != NULL);
					
				free(hashTable1[i]->numbers[j]->number);
				free(hashTable1[i]->numbers[j]);
			}
			free(hashTable1[i]->numbers);
			free(hashTable1[i]);

			hashTable1[i] = tmpNumBucket;			
		}while(hashTable1[i] != NULL);
			
	}
	if (mode == 1)
	{
		free(hashTable1);
	}

	for (i = 0; i < calleeHashEntries; ++i)
	{
		do{
			Bucket *tmpNumBucket = hashTable2[i]->next;

			for (j = 0; j < hashTable2[i]->curNumbers + 1; ++j)
			{
				do{
					CDRBucket *tmpRecBucket = hashTable2[i]->numbers[j]->calls->next;

					for (k = 0; k < hashTable2[i]->numbers[j]->calls->maxRecords; ++k)
					{
						if (hashTable2[i]->numbers[j]->calls->records[k] != NULL)
						{
							free(hashTable2[i]->numbers[j]->calls->records[k]->id);
							free(hashTable2[i]->numbers[j]->calls->records[k]);
						}
					}
					free(hashTable2[i]->numbers[j]->calls->records);
					free(hashTable2[i]->numbers[j]->calls);

					hashTable2[i]->numbers[j]->calls = tmpRecBucket;
				}while(hashTable2[i]->numbers[j]->calls != NULL);
					
				free(hashTable2[i]->numbers[j]->number);
				free(hashTable2[i]->numbers[j]);
			}
			free(hashTable2[i]->numbers);
			free(hashTable2[i]);

			hashTable2[i] = tmpNumBucket;			
		}while(hashTable2[i] != NULL);
			
	}
	if (mode == 1)
	{
		free(hashTable2);
	}
}