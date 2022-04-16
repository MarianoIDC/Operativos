#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "manage.h"

#define size 4096

int main(int argc, char *argv[]){
    //takes argument and tries to write it 
    if (argc != 1){
        printf("usage - %s //no args",argv[0]);
        return -1;
    }


    //try to attach in order to read
    char *block = attachMemoryBlock(FILENAME,size);
    if(block == NULL){
        printf("ERROR");
        return -1;
    }
    printf("Reading: \"%s\"\n", block);
   
    detachMemoryBlock(block);
    return 0; 
}
