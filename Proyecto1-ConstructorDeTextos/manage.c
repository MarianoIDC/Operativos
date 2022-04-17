#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "manage.h"
#include "dataTypes.h"

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

static int getSharedDataBlock(char *filename, int size, int num){
    key_t key;
    
    //request key
    key = ftok(filename, num);//key num
    if (key == IPC_RESULT_ERROR)
        return IPC_RESULT_ERROR;
    return shmget(key, size, 0664 | IPC_CREAT);
}

initGlobal *attachMemoryInfoBlock(char *filename, int size){
    int shareId = getSharedBlock(filename, size);
    initGlobal *result = malloc(size);

    if(shareId == IPC_RESULT_ERROR){
        return NULL;
    }

    result = (initGlobal *)shmat(shareId, NULL,0); //map the block into the address space
    if(result == (initGlobal *)IPC_RESULT_ERROR){
        return NULL;
    }
    return result;

}

data *attachMemoryDataBlock(char *filename, int size, int num){
    int shareId = getSharedDataBlock( filename, size, num);
    data *result = malloc(size);

    if(shareId == IPC_RESULT_ERROR){
        return NULL;
    }

    result = (data *)shmat(shareId, NULL,0); //map the block into the address space
    if(result == (data *)IPC_RESULT_ERROR){
        return NULL;
    }
    return result;

}

//done with memory block, take it away
bool detachMemoryInfoBlock(initGlobal *block){
    return(shmdt(block) !=IPC_RESULT_ERROR);
}

//done with memory block, take it away
bool detachMemoryDataBlock(data *block){
    return(shmdt(block) !=IPC_RESULT_ERROR);
}

//destroy isn't implemented (no neccessary)
//if need use shmctl(sharedId,IPC_RMID,NULL)

bool createMemoryBlock(char *filename, int size){
    int newFile = open(filename, O_RDWR | O_CREAT, 0777);
    if (newFile != -1)
        close(newFile);
    else
        return NULL;

    int sharedId = getSharedBlock(filename, size);
    if (sharedId == IPC_RESULT_ERROR)
        return NULL;
    return sharedId;
}

int getSharedId(char *filename, int size){
    return getSharedBlock(filename, size);
}

bool destroyMemoryInfoBlock(char *filename){
    int sharedId = getSharedBlock(filename, 0);

    if(sharedId == IPC_RESULT_ERROR)
        return NULL;

    bool result = (shmctl(sharedId, IPC_RMID, NULL) != IPC_RESULT_ERROR);
    result = result && (remove(filename) == 0);

    return result;
}