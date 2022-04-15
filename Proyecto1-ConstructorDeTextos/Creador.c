#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

<<<<<<< HEAD
int* globBlock; //global 
int* memBlock; //memory block
int* dtBlock; //date and time block
int* statsBlock; //stats block

int creator(){
=======
int main(){

    int* globBlock; //global 
    int* memBlock; //memory block
    int* dtBlock; //date and time block
    int* statsBlock; //stats block
    //int i;
>>>>>>> Creador

    //size enter by user
    int size;
    //id, data type
    int id;
    printf("Digite un espacio para la memoria, seguido del ID:");
    scanf("%d %d", &size, &id);
    printf("El espacio solicitado es de: %d\n", size);
    printf("ID: %d\n", id);
    //Id == 0 --> char
    if(id == 0){
        //global mem
        globBlock = (int*)malloc(2 * sizeof(char));
        globBlock[0] == id;
        globBlock[1] == 0;//global True or False with 0 or 1
        // Dynamically allocate memory using malloc() for char
        memBlock = (int*)malloc(size * sizeof(char));
        //init date and time memblock, size for time
        dtBlock = (int*)malloc(size * sizeof(time_t));//8 bytes I belive
        //init stats block
        statsBlock = (int*)malloc(5 * sizeof(time_t));

    }//Id != 0 --> int
    else{
        //global mem
        globBlock = (int*)malloc(2 * sizeof(int));
        globBlock[0] == id;
        globBlock[1] == 0;//global True or False with 0 or 1
        // Dynamically allocate memory using malloc() for int
        memBlock = (int*)malloc(size * sizeof(int));
        //init date and time memblock, size for time
        dtBlock = (int*)malloc(size * sizeof(time_t));//8 bytes I belive
        //init stats block
        statsBlock = (int*)malloc(5 * sizeof(timer_t));
    }
        
    if (memBlock == NULL && globBlock == NULL && dtBlock == NULL && statsBlock == NULL) {
        printf("Fallo en crear la memoria\n");
        exit(0);
    }
    else {
 
        // Memory has been successfully allocated
        printf("Memoria creada de: %d\n", size);
        
 
        /* Get the elements of the array
        for (i = 0; i < size; ++i) {
            memBlock[i] = i + 1;
        }
 
        // Print the elements of the array
        printf("The elements of the array are: ");
        for (i = 0; i < size; ++i) {
            printf("%d, ", memBlock[i]);
        }*/
    }

    //Malloc needs to be free
    free(globBlock);
    free(memBlock);
    free(dtBlock);
    free(statsBlock);
    return 0;
}


