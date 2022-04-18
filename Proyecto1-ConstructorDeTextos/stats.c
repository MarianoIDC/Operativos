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

stats stats_block = {
    .block_client = 0,
    .block_recons = 0,
    .transfer = 0,
    .total_memory = 0,
    .total_time = 0
};

int main(int argc, char *argv[]){
    printf("Waiting)");
    while(true){
        statsFunction();
    }    
    

    return 0;
}

void statsFunction(){
    sem_t *sem_create= sem_open(SEM_CREATE_FNAME, 0);
    if(sem_create==SEM_FAILED){
        printf("SEM CRE");
        //perror("sem_open/create");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_push= sem_open(SEM_PUSH_FNAME,0);
    if(sem_push==SEM_FAILED){
        printf("SEM PUSH");
        //perror("sem_open/push");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_pop= sem_open(SEM_POP_FNAME,0);
        if(sem_pop==SEM_FAILED){
            printf("SEM POP");
            //perror("sem_open/pop");
            exit(EXIT_FAILURE);
    }
    sem_t *sem_stats= sem_open(SEM_STATS_FNAME,0);
        if(sem_stats==SEM_FAILED){
            printf("SEM sTAT");
            //perror("sem_open/pop");
            exit(EXIT_FAILURE);
    }
    char *buffer_name= "mem.txt";
    printf("Waiting)");
    initGlobal *info_block = attachMemoryInfoBlock(buffer_name, INFO_SIZE);

    //initGlobal *info_block = attachMemoryDataBlock(buffer_name, INFO_SIZE);
    if(info_block==NULL){
        printf("ERROR INF");
        return -1;
    }
    printf("Waiting)");
    sem_wait(sem_stats);
    printf("Print");
    print_stats(info_block->stat);
    sem_close(sem_create);
    sem_close(sem_push);
    sem_close(sem_pop);
    sem_close(sem_stats);

    

    detachMemoryInfoBlock(info_block);

    
}