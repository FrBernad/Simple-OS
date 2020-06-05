#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#define MAX_PROCESSES 2

#include <stdint.h>
#include <screens.h>
#include <staticQueue.h>

typedef struct{
    void * entryPoint;
    void * rsp;
    void* rbp;
    int stackID;
    t_screenID screenID;
}t_PCB;

extern t_queue taskManager;

void* schedule(void* oldRSP, int forceStart);
int addProcess(t_PCB* process);
void killCurrentProcess();
void resetCurrentProcess();

#endif