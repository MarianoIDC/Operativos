#ifndef DATA_MANAGE
#define DATA_MANAGE

#include "dataTypes.h"


//the buffer works as a FIFO
//function for push the data from the circular buffer
data *push_data(cirBuffer *c, data data, char *buffer_name, semaph *sems);

//function for pop the data from the circular buffer
data *pop_data(cirBuffer *c, char *buffer_name, semaph *sems);

data *printMemory(cirBuffer *c, char *buffer_name);

#endif