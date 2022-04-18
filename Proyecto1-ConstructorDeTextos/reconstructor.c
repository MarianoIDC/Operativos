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
#define SIZE 20

const char * filename= "reconstructor.txt";
int concatChar(const char * filename, char value);

int main(int argc, char *argv[]){
    rebuildFile();
    return 0;
}

void rebuildFile(){
    int i;
    char *buffer_name= "mem.txt";
    remove(filename);
    initGlobal *info_block = attachMemoryInfoBlock(buffer_name, INFO_SIZE);
    //initGlobal *info_block = attachMemoryDataBlock(buffer_name, INFO_SIZE);
    if(info_block==NULL){
        printf("ERROR INF");
        return -1;
    }
    int instance_id = getSharedId(buffer_name, INFO_SIZE);
    
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
    semaphtest sem_using = {
        .semCreate = sem_create,
        .semPush = sem_push,
        .semPop = sem_pop
    };

	// Print the elements of the array
    
    for (i = 0; i < SIZE; ++i) {
        sem_wait(sem_pop);
        printf("\n Press ENTER key to Continue\n"); 
        getchar();
        //printf("Memory address: 0x%08x with value %c\n", &memory+i,memory[i]);
        FILE *fp = fopen(filename, "ab");
        if(NULL == fp)
        {
            printf("[-]Error opening file.");
            //return 0;
        }
        
        data *dataptr= pop_data(&info_block->buff, buffer_name, &sem_using);
        //fputc(memory[i],fp);
        fclose(fp);
        concatChar(filename,dataptr->data);
        readFile(filename);
        //printf("\nPOP VALUE: %c, \n", dataptr->data);
        //printf("\nIndex VALUE: %c, \n", dataptr->index);
        sem_post(sem_push);
        sem_post(sem_create);
    }sem_close(sem_create);
    sem_close(sem_push);
    sem_close(sem_pop);

    detachMemoryInfoBlock(info_block);


}

int readFile(const char * filename){
    /* Create file where data will be stored */
    char ch;
    FILE *fp = fopen(filename, "r");
    if(NULL == fp)
    {
        printf("[-]Error opening file.");
        return 0;
    }
    printf("****************************************\n");
    printf("**************BUILD FILE*****************\n");
    printf("****************************************\n");
    do {
        ch = fgetc(fp);
        printf("%c", ch);
        // Checking if character is not EOF.
        // If it is EOF stop eading.
    } while (ch != EOF);
    fclose(fp);
    printf("\n**************END FILE******************\n");
    return 1;
}
int concatChar(const char * filename, char value){
    /* Create file where data will be stored */
    FILE *fp = fopen(filename, "ab");
    if(NULL == fp)
    {
        printf("[-]Error opening file.");
        return 0;
    }
    fputc(value,fp);
    fclose(fp);
    return 1;
}