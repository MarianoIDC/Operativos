#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 128 
#define RSIZ 10 

int main(void) 
{

    /*
    char line[RSIZ][LSIZ];
	char* fname="conf.ini";
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    char* PORT=line[1];
    char* PATH=line[3]; 
    printf(" %s\n", PORT);
    printf(" %s\n", PATH);
    printf("\n");
    return 0;

    */
   int PORT=getPort();
    printf(" %d\n", PORT);
    char* PATH= getPath();
}

int getPort(){

    char line[RSIZ][LSIZ];
	char* fname="conf.ini";
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    char* temp=line[1];
    int PORT = atoi(temp);
    //printf(" %d\n", PORT);
    return PORT;
}

char* getPath(){

    char line[RSIZ][LSIZ];
	char* fname="conf.ini";
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    char* PATH =line[3];
    //printf(" %d\n", PORT);
    return PATH;
}