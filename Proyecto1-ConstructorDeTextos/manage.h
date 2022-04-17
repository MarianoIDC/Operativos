#ifndef MANAGE
#define MANAGE

#include <stdbool.h>
#include "dataTypes.h"

int getSharedId(char *filename, int size);
initGlobal *attachMemoryInfoBlock(char *filename, int size);
data *attachMemoryDataBlock(char *filename, int size, int buffer_size);
bool detachMemoryInfoBlock(initGlobal *block);
bool detachMemoryDataBlock(data *block);
bool createMemoryBlock(char *filename, int size);

//char * attachMemoryBlock(char *filename, int size);
//bool detachMemoryBlock(char *block);


//all the programs will share... 
//#define FILENAME "initShareMem.txt"
//#define SIZE 4096

#endif