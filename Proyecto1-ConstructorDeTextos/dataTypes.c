#include <stdio.h>
#include <time.h>
#include "dataTypes.h"

void printData(data * dataI, char * instance_name, int instance_id, double t)
{
    printf("\n");
    printf("--------------------------------------\n");
    printf("%i on index: %i\n",  instance_id, dataI->index);
    printf("Data Added Date: %s", ctime(&dataI->current_time));
    printf("Data: %c\n", dataI->data);
    //printf("Waited: %lf seconds\n", t);
    printf("--------------------------------------\n");
    printf("\n");
}


void printPop(data* dataI)
{
    printf("\n");
    printf("--------------------------------------\n");
    printf("Memory index: %i\n",  dataI->index);
    printf("Data Added Date: %s", ctime(&dataI->current_time));
    printf("Data: %c\n", dataI->data);
    //printf("Waited: %lf seconds\n", t);
    printf("--------------------------------------\n");
    printf("\n");
}

void print_stats(stats stat)
{
    printf("\n");
    printf("\033[0;32m");
    printf("--------------------------------------\n");
    printf("Stats\n");
    printf("Data Transfered: %i\n",stat.transfer-1);
    printf("Client Wait Time: %lf\n", stat.block_client);
    printf("Reconstructor wait time: %lf\n", stat.block_recons);
    printf("Memory usage: %lf\n", stat.transfer+12);
    printf("Total time: %lf\n", stat.total_time);
    printf("--------------------------------------\n");
    printf("\033[0m");
    printf("\n");
}