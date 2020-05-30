#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#define MAX_PROCESSES 2

#include <stdint.h>
#include <staticQueue.h>
#include <applications.h>

extern t_queue taskManager;

void addProcess(t_application* app);
void changeProcess(/*uint64_t* rip, uint64_t* rsp*/);
void runProcess(/*uint64_t* rip, uint64_t* rsp*/);

#endif