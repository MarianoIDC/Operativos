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

//semaphtest
typedef struct{
    sem_t semCreate;
    sem_t semPush;
    sem_t semPop;
}semaphtest;

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
    char data;
}data;


//stats info
typedef struct{
    double block_client;
    double block_recons;
    int transfer;
    double total_memory;
    double total_time;
}stats;

//global data, should be share with all process
typedef struct{
    char data[SIZE];
    semaph semaphores;
    int size;
    cirBuffer buff;
    bool stop;
    stats stat;
    
}initGlobal;

void printData(data * data, char * instance_name, int instance_id, double t);
void print_stats(stats stat);



#endif