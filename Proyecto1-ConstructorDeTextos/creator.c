#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include "manage.h"
#include "dataTypes.h"
#include "dataManage.h"
#include <sys/ipc.h>
#include <fcntl.h>

#define INFO_SIZE sizeof(initGlobal)
#define DATA_SIZE sizeof(data)

int main(int argc, char *argv[]){
    char *buffer_name = "mem.txt";
    int size = 250;
    printf("Digite un espacio para la memoria:");
    scanf("%d", &size);
    printf("El espacio solicitado es de: %d\n", size);

    for (int i = 0; i < argc; ++i)
        if (!strcmp(argv[i], "-n"))
            buffer_name = argv[++i];
        else if (!strcmp(argv[i], "-s"))
            size = atoi(argv[++i]);

    if (buffer_name == NULL || size < 1)
    {
        printf("Couldn't create Block: %s\n", buffer_name);
        return -1;
    }

    if (createMemoryBlock(buffer_name, INFO_SIZE))
        printf("Created Block: %s\n", buffer_name);
    else
    {
        printf("Couldn't create Block: %s\n", buffer_name);
        return -1;
    }

    initGlobal dataI = {
        .size = size,
        .buff = {
            .head = 0,
            .tail = 0,
            .mxlen = size}
    };

    strcpy(dataI.data, buffer_name);

    initGlobal *data_ptr = &dataI;
    initGlobal *info_block = attachMemoryInfoBlock(buffer_name, INFO_SIZE);

    if (info_block == NULL)
    {
        printf("ERROR: couldn't get Block: %s\n", buffer_name);
        return -1;
    }

    printf("INFOR...");
    printf("%d",info_block->buff.head+1);
        
    int instance_id = getSharedId(buffer_name, size);
    memcpy(info_block, data_ptr, INFO_SIZE);
    sem_unlink(SEM_CREATE_FNAME);
    sem_unlink(SEM_POP_FNAME);
    sem_unlink(SEM_PUSH_FNAME);


    sem_t *sem_create= sem_open(SEM_CREATE_FNAME,  O_CREAT | O_EXCL,0660,1);
    if(sem_create==SEM_FAILED){
        printf("SEM CREATE");
        //perror("sem_open/create");
        exit(EXIT_FAILURE);
    }

    sem_t *sem_push= sem_open(SEM_PUSH_FNAME,  O_CREAT | O_EXCL,0660,0);
    if(sem_push==SEM_FAILED){
        printf("SEM PUSH");
        //perror("sem_open/push");
        exit(EXIT_FAILURE);
    }


    sem_t *sem_pop= sem_open(SEM_POP_FNAME,  O_CREAT | O_EXCL,0660,0);
        if(sem_pop==SEM_FAILED){
            printf("SEM POP");
            //perror("sem_open/pop");
            exit(EXIT_FAILURE);
    }
    

    //sem_wait(&info_block->semaphores.empty);
    //sem_post(&info_block->semaphores.empty)
    int i =0;
   while(true){
       printf("while...");
        sem_wait(sem_create);
        //printf(info_block->buff.head);
        //i++;
        printData(dataI.data, buffer_name, instance_id, 2.0);
        sem_post(sem_push);
        sem_post(sem_pop);
       
    }
    sem_close(sem_create);
    sem_close(sem_push);
    sem_close(sem_pop);

    detachMemoryInfoBlock(info_block);

    return 0;
}


