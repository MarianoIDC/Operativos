#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include "manage.h"
#include "dataTypes.h"
#include "dataManage.h"

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
        
    int instance_id = getSharedBlock(buffer_name, size);
    memcpy(info_block, data_ptr, INFO_SIZE);

    sem_init(&info_block->semaphores.usage_sem, 1, 1);
    sem_init(&info_block->semaphores.full, 1, 1);
    sem_init(&info_block->semaphores.empty, 1, 1);

    sem_wait(&info_block->semaphores.empty);

    detachMemoryInfoBlock(info_block);
    
    printf(instance_id);
   /*while(true){
        printData(dataI.data, buffer_name, instance_id, 2.0);
    }*/

    return 0;
}


