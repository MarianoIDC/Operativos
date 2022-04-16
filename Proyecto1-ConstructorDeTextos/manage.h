#ifndef MANAGE
#define MANAGE

#include <stdbool.h>
#include "dataTypes.h"


//init_global *attach_memory_info_block(char *name, int size);
//data *attach_memory_data_block(char *name, int size, int buffer_size);
//bool detach_memory_info_block(initialization_data_t *block);
//bool detach_memory_data_block(data_t *block);

char * attachMemoryBlock(char *filename, int size);
bool detachMemoryBlock(char *block);


//all the programs will share... 
#define FILENAME "initShareMem.txt"
//#define SIZE 4096

#endif