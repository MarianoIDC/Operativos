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
    if (argc ==2){
        char *filename = argv[1];
        readFile(filename);
    }else{
        printf("[-]Invalid number of argument, usage is %s [FILENAME]\n",argv[0]);
    }

   
    return 0;

}

void readFile(char *filename){
    char *buffer_name= "mem.txt";
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

    //FILE PARAMETERS
    FILE* filePtr;
	char ch;
    time_t t;
    struct tm *tm;
    char fechayhora[100];
	// Opening file in reading mode
	filePtr = fopen(filename, "r");

	if (NULL == filePtr) {
		printf("file can't be opened \n");
	}

	printf("Press Enter to read the file... \n");

	// Printing what is written in file
	// character by character using loop.
	do {
        char c = getchar();
        if (c==10)
        {
            if(!info_block->stop){
                ch = fgetc(filePtr);
                t=time(NULL);
                tm=localtime(&t);
                strftime(fechayhora, 100, "%d/%m/%Y-%H:%M:%S", tm);
                
                //printf ("Dato: %c, logtime>>> %s\n", ch, fechayhora);
                data dataI = {
                    .key = 0,
                    .index = 0,
                    .current_time = t,
                    .data = ch
                };
                sem_wait(sem_push);
                //data *dataptr =NULL;
                data *dataptr = push_data(&info_block->buff, dataI,buffer_name, &sem_using);
                if(dataptr!=NULL){
                    printData(dataptr,"mem.txt",instance_id,2.0);
                    
                }else{
                    printf("IS NULL");
                    //sem_post(sem_pop);
                    break;
                }sem_post(sem_create);
                sem_post(sem_pop);
            }          
        }
		// Checking if character is not EOF.
		// If it is EOF stop eading.
	} while (ch != EOF);
    info_block->stop=true;
    sem_post(sem_pop);
    sem_close(sem_create);
    sem_close(sem_push);
    sem_close(sem_pop);
    detachMemoryInfoBlock(info_block);

	// Closing the file
	fclose(filePtr);
}