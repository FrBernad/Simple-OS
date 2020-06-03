#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#define MAX_PROCESSES 2

#include <stdint.h>
#include <staticQueue.h>
#include <applications.h>

typedef struct{
    void * rsp;
    void * rbp;
    t_screenID screenID;
}t_PCB;

extern t_queue taskManager;

void addProcess(t_application* app);
uint64_t schedule(uint64_t oldRSP, int forceStart);

#endif