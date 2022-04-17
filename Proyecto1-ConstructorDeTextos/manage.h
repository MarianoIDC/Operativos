#ifndef MANAGE
#define MANAGE

#include <stdbool.h>
#include "dataTypes.h"

#define SEM_CREATE_FNAME "/create"
#define SEM_PUSH_FNAME "/push"
#define SEM_POP_FNAME "/pop"
int getSharedId(char *filename, int size);
initGlobal *attachMemoryInfoBlock(char *filename, int size);
data *attachMemoryDataBlock(char *filename, int size, int buffer_size);
bool detachMemoryInfoBlock(initGlobal *block);
bool detachMemoryDataBlock(data *block);
bool createMemoryBlock(char *filename, int size);
bool destroyMemoryInfoBlock(char *filename, int size);

//char * attachMemoryBlock(char *filename, int size);
//bool detachMemoryBlock(char *block);


//all the programs will share... 
//#define FILENAME "initShareMem.txt"
//#define SIZE 4096

#endif