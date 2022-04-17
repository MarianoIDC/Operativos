#include <stdio.h>
#include <time.h>
#include "dataTypes.h"

void printData(data * dataI, char * instance_name, int instance_id, double t)
{
    printf("\n");
    printf("--------------------------------------\n");
    printf("%s %i on index: %i\n", instance_name, instance_id, dataI->index);
    printf("Message Emited Date: %s", ctime(&dataI->current_time));
    printf("Message: %c\n", dataI->data);
    printf("Waited: %lf seconds\n", t);
    printf("--------------------------------------\n");
    printf("\n");
}