#include "stringManipulate.h"

char *inputString(FILE* fp, size_t size){
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

void printCDR(CDR record){
	printf("\t%s;", record.id);
	printf("%03d-", record.callerOrigin);
	printf("%010ld;", record.callerNum);
	printf("%03d-", record.calleeOrigin);
	printf("%010ld;", record.calleeNum);
	printf("%ld", (((record.day) % 365) % 30));
	printf("%ld", (((record.day) % 365) / 30) + 1);
	printf("%ld;", ((record.day) / 365) + 1);
	printf("%d:", (record.min / 60));
	printf("%d;", (record.min % 60));
	printf("%d;", record.duration);
	printf("%d;", record.type);
	printf("%d;", record.tarrif);
	printf("%ld\n", record.fault);
}

void printFileCDR(FILE *fp, CDR record){
	fprintf(fp, "%s;", record.id);
	fprintf(fp, "%03d-", record.callerOrigin);
	fprintf(fp, "%010ld;", record.callerNum);
	fprintf(fp, "%03d-", record.calleeOrigin);
	fprintf(fp, "%010ld;", record.calleeNum);
	fprintf(fp, "%ld", (((record.day) % 365) % 30));
	fprintf(fp, "%ld", (((record.day) % 365) / 30) + 1);
	fprintf(fp, "%ld;", ((record.day) / 365) + 1);
	fprintf(fp, "%d:", (record.min / 60));
	fprintf(fp, "%d;", (record.min % 60));
	fprintf(fp, "%d;", record.duration);
	fprintf(fp, "%d;", record.type);
	fprintf(fp, "%d;", record.tarrif);
	fprintf(fp, "%ld\n", record.fault);
}