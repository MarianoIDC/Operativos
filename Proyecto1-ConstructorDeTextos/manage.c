#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include "manage.h"

#define IPC_RESULT_ERROR (-1)

// needs the file name and the block size
// return the id of the shared memory block
static int getSharedBlock(char *filename, int size){
    key_t key;

    //request key
    key = ftok(filename, 0);// key 0 
    if(key == IPC_RESULT_ERROR){
        return IPC_RESULT_ERROR;
    }

    //get shared block id
    return shmget(key, size, 0644 | IPC_CREAT);//load or create a shared mem block
}

char *attachMemoryBlock(char *filename, int size){
    int shareId = getSharedBlock( filename, size);
    char *result;

    if(shareId == IPC_RESULT_ERROR){
        return NULL;
    }

    result = shmat(shareId, NULL,0); //map the block into the address space
    if(result == (char *)IPC_RESULT_ERROR){
        return NULL;
    }
    return result;

}
//done with memory block, take it away
bool detachMemoryBlock(char *block){
    return(shmdt(block) !=IPC_RESULT_ERROR);
}

//destroy isn't implemented (no neccessary)
//if need use shmctl(sharedId,IPC_RMID,NULL)