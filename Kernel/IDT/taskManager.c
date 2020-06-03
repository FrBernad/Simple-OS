#include <interrupts.h>
#include <keyboardDriver.h>
#include <lib.h>
#include <stringLib.h>
#include <taskManager.h>
#include <videoDriver.h>

#define SIZE_OF_STACK 4 * 1024

static void * getNewStackBase();
// static void initializeStackFrame(t_PCB* pcb, uint64_t rip);

typedef struct {
      //Registers restore context
      uint64_t gs;
      uint64_t fs;
      uint64_t r15;
      uint64_t r14;
      uint64_t r13;
      uint64_t r12;
      uint64_t r11;
      uint64_t r10;
      uint64_t r9;
      uint64_t r8;
      uint64_t rsi;
      uint64_t rdi;
      uint64_t rbp;
      uint64_t rdx;
      uint64_t rcx;
      uint64_t rbx;
      uint64_t rax;

      //iretq hook
      uint64_t rip;
      uint64_t cs;
      uint64_t eflags;
      uint64_t rsp;
      uint64_t ss;
      uint64_t base;

      uint64_t ret;
} stack_frame;

void callProcess(int cargs, void** pargs, void* entryPoint) {
      printStringLn("hola");
      ((int (*)(int, void**))(entryPoint))(cargs, pargs);

      // sys_leave(0, 0, 0, 0, 0);
}

void* fill_stack(void* entryPoint, void* stack_base, int cargs, void** pargs) {
      stack_frame* frame = (stack_frame*)(stack_base - sizeof(stack_frame) - 1);

      frame->gs = 0x001;
      frame->fs = 0x002;
      frame->r15 = 0x003;
      frame->r14 = 0x004;
      frame->r13 = 0x005;
      frame->r12 = 0x006;
      frame->r11 = 0x007;
      frame->r10 = 0x008;
      frame->r9 = 0x009;
      frame->r8 = 0x00A;
      frame->rsi = pargs;
      frame->rdi = cargs;
      frame->rbp = 0x00D;
      frame->rdx = entryPoint;
      frame->rcx = 0x00F;
      frame->rbx = 0x010;
      frame->rax = 0x011;

      //iret hook
      frame->rip = (void*)&callProcess;
      frame->cs = 0x008;
      frame->eflags = 0x202;
      frame->rsp = (uint64_t) & (frame->base);
      frame->ss = 0x000;
      frame->base = 0x000;

      return (void*)frame;
}

//PROCESS CONTROL BLOCK

static t_PCB processes[MAX_PROCESSES];

static uint8_t stacks[MAX_PROCESSES][SIZE_OF_STACK], stackIndex = 0;

t_queue taskManager = {processes, 0, -1, 0, MAX_PROCESSES, sizeof(t_PCB)};

uint64_t schedule(uint64_t oldRSP, int forceStart) {
      t_PCB currentProcess, nextProcess;

      printStringLn("Scheduling...");

      if (!forceStart) {
            queueRemoveData(&taskManager, &currentProcess);
            currentProcess.rsp = oldRSP;
            queueInsert(&taskManager, &currentProcess);
      }

      if (forceStart) {
            printStringLn("Forcing start...");
      }

      queuePeek(&taskManager, &nextProcess);

      printString("Process on screen ");
      printInt(nextProcess.screenID);
      putchar('\n');

      changeScreen(nextProcess.screenID);
      changeBuffer(nextProcess.screenID);

      printString("A punto de retornar");

      return nextProcess.rsp;
}

void addProcess(t_application* app) {
      printString("Adding Process to screen");
      printInt(app->screenID);
      putchar('\n');

      t_PCB newPCB;
      newPCB.rbp = getNewStackBase();
      newPCB.screenID = app->screenID;
      printStringLn("entro");
      newPCB.rsp = fill_stack((void*)app->entryPoint, (void*)(newPCB.rbp),0 , 0);
      printStringLn("salgo");
      // initializeStackFrame(&newPCB, (uint64_t)app->entryPoint);
      queueInsert(&taskManager, &newPCB);
}

// 0000
//
//
//
//
//
//
//
// FFFF

// static void initializeStackFrame(t_PCB* pcb, uint64_t rip) {
//       t_stackFrame SF;
//       SF.rip = rip;
//       SF.cs = 0x8;
//       SF.rflags = 0x202;
//       SF.rsp = pcb->rbp - sizeof(SF);
//       SF.ss = 0x0;

//       memcpy((void*)pcb->rsp, &SF, sizeof(SF));
// }

static void* getNewStackBase() {
      return stacks[stackIndex++];
}

// void addProcess(t_application* app) {
//       // app->stack=stacks[stackIndex++];
//       queueInsert(&taskManager, app);
// }

// void changeProcess(uint64_t* stackframe) {
//       t_application currentProcess, nextProcess;
//       queueRemoveData(&taskManager, &currentProcess);
//       queuePeek(&taskManager, &nextProcess);
//       changeScreen(nextProcess.screenID);
//       changeBuffer(nextProcess.screenID);
//       queueInsert(&taskManager, &currentProcess);
//       stackframe[0] = (uint64_t)nextProcess.app;
//       // stackframe[3] = (uint64_t)nextProcess.stack;      queueRemoveData(&taskManager, &currentProcess);
//       queuePeek(&taskManager, &nextProcess);
//       changeScreen(nextProcess.screenID);
//       changeBuffer(nextProcess.screenID);
//       queueInsert(&taskManager, &currentProcess);
//       stackframe[0] = (uint64_t)nextProcess.app;
//       // stackframe[3] = (uint64_t)nextProcess.stack;
// }
