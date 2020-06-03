#include <applications.h>
#include <interrupts.h>
#include <keyboardDriver.h>
#include <sizeof.h>
#include <stringLib.h>
#include <taskManager.h>
#include <videoDriver.h>

static t_application processes[MAX_PROCESSES];

static uint8_t stacks[MAX_PROCESSES][4 * MB],stackIndex=0;
t_queue taskManager = {processes, 0, -1, 0, MAX_PROCESSES, POINTER + POINTER + INTEGER + POINTER};

void addProcess(t_application* app) {
      // app->stack=stacks[stackIndex++];
      queueInsert(&taskManager, app);
}

void changeProcess(uint64_t* stackframe) {
      t_application currentProcess, nextProcess;
      queueRemoveData(&taskManager, &currentProcess);
      queuePeek(&taskManager, &nextProcess);
      changeScreen(nextProcess.screenID);
      changeBuffer(nextProcess.screenID);
      queueInsert(&taskManager, &currentProcess);
      stackframe[0] = (uint64_t)nextProcess.app;
      // stackframe[3] = (uint64_t)nextProcess.stack;
}

void runProcess(uint64_t* stackframe) {
      t_application currentProcess;
      queuePeek(&taskManager, &currentProcess);
      changeScreen(currentProcess.screenID);
      changeBuffer(currentProcess.screenID);
      stackframe[0] = (uint64_t)currentProcess.app;
      // stackframe[3] = (uint64_t)currentProcess.stack;
}
