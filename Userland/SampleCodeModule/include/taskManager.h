#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#define MAX_TASKS 2

#include <screens.h>

typedef struct {
      void* entryPoint;
      void* rsp;
      void* rbp;
      int stackID;
      t_screenID screenID;
} t_PCB;

void initApps();

#endif