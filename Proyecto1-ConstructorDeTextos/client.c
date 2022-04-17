#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include "manage.h"
#include "dataTypes.h"
#include "dataManage.h"
#include <time.h>
#include <unistd.h>
#define INFO_SIZE sizeof(initGlobal)

int main(int argc, char *argv[]){
    char *buffer_name= "mem.txt";
    initGlobal *info_block = attachMemoryInfoBlock(buffer_name, INFO_SIZE);
    if(info_block==NULL){
        print("ERROR INF");
        return -1;
    }
    int instance_id = getSharedId(buffer_name, INFO_SIZE);
    time_t t;   // not a primitive datatype
    time(&t);

    


    sem_t *sem_create= sem_open(SEM_CREATE_FNAME, 0);
    if(sem_create==SEM_FAILED){
        //perror("sem_open/create");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_push= sem_open(SEM_PUSH_FNAME,0);
    if(sem_push==SEM_FAILED){
        //perror("sem_open/push");
        exit(EXIT_FAILURE);
    }


    sem_t *sem_pop= sem_open(SEM_POP_FNAME,0);
        if(sem_pop==SEM_FAILED){
            //perror("sem_open/pop");
            exit(EXIT_FAILURE);
    }

    while (!info_block->stop)
    {
        data dataI = {
        .key = 0,
        .index = 0,
        .current_time = t,
        .data = 125
        };
        data *dataptr = push_data(&info_block->buff, dataI,buffer_name, &info_block->semaphores);
        if(dataptr!=NULL){
            printData(dataptr,"test",instance_id,2.0);
        }else{
            printf("IS NULL");
            break;
        }
    }
    
    
    sem_wait(sem_push);
   printf("SEmAFORO PUSH");
    sem_post(sem_create);


    sem_close(sem_create);
    sem_close(sem_push);
    sem_close(sem_pop);

    detachMemoryInfoBlock(info_block);
   
   
    return 0;

}