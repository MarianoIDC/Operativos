#ifndef DATATYPE
#define DATATYPE

#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>
#include <time.h>

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

}buffer;

typedef struct{
    int key;
    int index;
    time_t current_time;
    int data;

}data;

//global data, should be share with all process
typedef struct{
    semaph semaphores;
    int size;
    buffer buff;
    bool stop;
    int N;
    char data[];

}init_global;

//stats info
typedef struct{
    int data;
    double block_client;
    double block_recons;
    int transf;
    double total_memory;
    double total_time;
}stats;






#endif