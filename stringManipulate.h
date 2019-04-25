#ifndef STRINGMANIPULATE
#define STRINGMANIPULATE

#include <stdio.h>
#include <stdlib.h>
#include "hashStructs.h"

/*Reads all the data ot fp until it finds '\n' and returns a string pointer to it*/
char *inputString(FILE* fp, size_t size);

/*Prints a cdr*/
void printCDR(CDR record);

/*Prints a cdr to a filepointer in the format that it was inserted*/
void printFileCDR(FILE *fp, CDR record);
#endif