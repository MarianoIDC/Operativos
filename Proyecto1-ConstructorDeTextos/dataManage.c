#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dataTypes.h"
#include "manage.h"

#define BLOCK_SIZE sizeof(data)


static bool full(cirBuffer *c){
    
    int next_push = c->head + 1;
    //if next push is greater or equal than mxlen
    //is_gt_size is true 
    //the next push is on the first element
    const bool is_gt_size = next_push >= c->mxlen;
    
    if (is_gt_size)
        next_push = 0;

    return next_push == c->tail;
}

static bool empty(cirBuffer *c){
    return c->head == c->tail;
}

data *push_data(cirBuffer *c, data dataI, char *buffer_name, semaph sems){
    //action is push so we need to be clear that the resource will be in use
    //then the semaphore is called for usage
    //sem_wait(&sems.usage_sem);

    //verify if is empty or full
    const bool was_empty = empty(c);
    const bool is_full = full(c);

    // if true the full sems is called
    if (is_full)
        printf("IS FULL");
        //sem_wait(&sems.full);

    int next = c->head + 1;
    
    const bool is_gt_size = next >= c->mxlen;
    if (is_gt_size)
        next = 0;

    int i = c->head;
    dataI.index = i;
    data *buffer_val = attachMemoryDataBlock(buffer_name, BLOCK_SIZE, i + 1);

    if (buffer_val == NULL)
        return NULL;

    *buffer_val = dataI;
    c->head = next;
    data *response = (data *)malloc(sizeof(data));
    *response = *buffer_val;
    detachMemoryDataBlock(buffer_val);
    //re-verify if empty or full
    if (full(c))
        printf("FULL");
        //sem_wait(&sems.full);

    if(was_empty)
        printf("EMPTY \n");
        //sem_post(&sems.empty);

    //sem_post(&sems.usage_sem);
    return response;
}

data *printMemory(cirBuffer *c, char *buffer_name){
    const bool was_full = full(c);
    const bool is_empty = empty(c);

    if (is_empty)
        printf("EMPTY");
        //sem_wait(&sems.empty);

    int next = c->tail + 1;
    const bool is_gt_size = next >= c->mxlen;
    if (is_gt_size)
        next = 0;

    int i = c->tail;
    data *buffer_val = attachMemoryDataBlock(buffer_name, BLOCK_SIZE, i + 1);

    data *dataI = (data *)malloc(sizeof(data));
    *dataI = *buffer_val;

    c->tail = next;
    detachMemoryDataBlock(buffer_val);
    
    
    if (empty(c)){
        printf("EMPTY \n");
        return NULL;
    }
        //sem_wait(&sems.empty);

    if(was_full)
        printf("FULL");
        //sem_post(&sems.full);
        printf("\n");
    printf("--------------------------------------\n");
    printf("---------------MEMORY-----------------\n");
    printf("Memory index: %i\n", dataI->index);
    printf("Message Emited Date: %s", ctime(&dataI->current_time));
    printf("Message: %c\n", dataI->data);
    //printf("Waited: %lf seconds\n", t);
    printf("--------------------------------------\n");
    printf("\n");
    //sem_post(&sems.usage_sem);
    return dataI;
}


data *pop_data(cirBuffer *c, char *buffer_name, semaph sems){
    //sem_wait(&sems.usage_sem);

    const bool was_full = full(c);
    const bool is_empty = empty(c);

    if (is_empty)
        printf("EMPTY");
        //sem_wait(&sems.empty);

    int next = c->tail + 1;
    const bool is_gt_size = next >= c->mxlen;
    if (is_gt_size)
        next = 0;

    int i = c->tail;
    data *buffer_val = attachMemoryDataBlock(buffer_name, BLOCK_SIZE, i + 1);

    data *dataI = (data *)malloc(sizeof(data));
    *dataI = *buffer_val;

    c->tail = next;
    detachMemoryDataBlock(buffer_val);
    
    
    if (empty(c)){
        printf("EMPTY \n");
        return NULL;
    }
        //sem_wait(&sems.empty);

    if(was_full)
        printf("FULL");
        //sem_post(&sems.full);

    //sem_post(&sems.usage_sem);
    return dataI;
}