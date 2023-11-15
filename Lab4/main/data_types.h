#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#include <stdio.h>

#define QUEUE_SIZE          10
#define QUEUE_WAITS         200
#define QUEUE_SEND_WAITS    300
#define QUEUE_SEND_DELAY    500


typedef struct {
    int ID;
    int dataType;
} Task;

#endif 