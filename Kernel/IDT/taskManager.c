#include <applications.h>
#include <interrupts.h>
#include <keyboardDriver.h>
#include <sizeof.h>
#include <stringLib.h>
#include <taskManager.h>
#include <videoDriver.h>

static t_application processes[MAX_PROCESSES];

t_queue taskManager = {processes, 0, -1, 0, MAX_PROCESSES, POINTER + INTEGER};

void addProcess(t_application* app) {
      queueInsert(&taskManager, app);
}

void changeProcess(/*uint64_t* rip, uint64_t* rsp*/) {
      // putchar('\n');
      // for (int i = 0; i < MAX_PROCESSES; i++) {
      //       printString("current Screen:");
      //       printInt(processes[i].screenID);
      //       putchar('\n');
      // }
      t_application currentProcess, nextProcess;
      queueRemoveData(&taskManager, &currentProcess);
      queuePeek(&taskManager, &nextProcess);
      changeScreen(nextProcess.screenID);
      changeBuffer(nextProcess.screenID);
      // for (int i = 0; i < MAX_PROCESSES; i++) {
      //       printString("current Screen:");
      //       printInt(processes[i].screenID);
      //       putchar('\n');
      // }
      queueInsert(&taskManager, &currentProcess);
      _sti();
      nextProcess.app();
      // *rip = (uint64_t)currentProcess.app;
}

void runProcess(/*uint64_t* rip, uint64_t* rsp*/) {
      t_application currentProcess;
      queuePeek(&taskManager, &currentProcess);
      changeScreen(currentProcess.screenID);
      changeBuffer(currentProcess.screenID);
      _sti();
      currentProcess.app();
   //   *rip=(uint64_t)currentProcess.app;
      //WTFFFFFF
      //  for (int i = 0; i < MAX_PROCESSES; i++)
      //  {
      //        printString("current Screen:");
      //        printInt(processes[i].screenID);
      //        putchar('\n');
      //  }
}
