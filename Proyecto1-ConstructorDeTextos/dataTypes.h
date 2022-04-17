#ifndef DATATYPE
#define DATATYPE

#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>
#include <time.h>

#define SIZE 255

//semaphores needed
typedef struct{
    sem_t usage_sem;
    sem_t full;
    sem_t empty;
}semaph; 

//buffer data 
typedef struct{
    int head;
    int tail;
    int mxlen;
}cirBuffer;

typedef struct{
    int key;
    int index;
    time_t current_time;
    int data;
}data;

//global data, should be share with all process
typedef struct{
    char data[SIZE];
    semaph semaphores;
    int size;
    cirBuffer buff;
    bool stop;
    
}initGlobal;

//stats info
typedef struct{
    double block_client;
    double block_recons;
    int transfer;
    double total_memory;
    double total_time;
}stats;

void printData(data * data, char * instance_name, int instance_id, double t);
void printStats(stats stats, char * instance_name, int instance_id);




#endif