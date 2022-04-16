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
    if (argc != 2){
        printf("usage - %s [stuff to write]",argv[0]);
        return -1;
    }
    //size enter by user
    //int size;
    //id, data type
    //int id;
    //printf("Digite un espacio para la memoria, seguido del ID:");
    //scanf("%d", &size);
    //printf("El espacio solicitado es de: %d\n", size);

    //try to attach in order to write
    char *block = attachMemoryBlock(FILENAME,size);
    if(block == NULL){
        printf("ERROR");
        return -1;
    }
    printf("Writing: \"%s\"\n", argv[1]);
    //copy thge arg into the shared block of memory
    strncpy(block, argv[1], size);

    detachMemoryBlock(block);
    return 0; 
}


