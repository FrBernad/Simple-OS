
#include <applications.h>
#include <interrupts.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <taskManager.h>
#include <utils.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6
#define REGISTERS 17

static void zero_division();
static void invalid_op_code();
static void printRegisters(uint64_t* registers);

// extern t_queue taskManager;

void exceptionDispatcher(int exception, uint64_t* stackframe, uint64_t* registers) {
      // t_application currentProcess;
      // queuePeek(&taskManager, &currentProcess);
      // stackframe[0] = (uint64_t)currentProcess.reset;
      // stackframe[3] = (uint64_t)currentProcess.stack;
      putchar('\n');
      switch (exception) {
            case ZERO_EXCEPTION_ID:
                  zero_division();
                  break;

            case INVALID_OPCODE_ID:
                  invalid_op_code();
                  break;
      }
      printRegisters(registers);
      sys_changeProcess();
}

static void zero_division() {
      printStringWC("Warning: division by zero is undefined\n", BLACK, RED);
}

static void invalid_op_code() {
      printStringWC("Invalid Opcode\n", BLACK, RED);
}

static void printRegisters(uint64_t* registers) {
      char* regNames[] = {"rsp", "rbp", "rip", "rax", "rcx", "rdx", "rbx", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
      for (int i = 0; i < REGISTERS; i++) {
            printStringWC(" > ", BLACK, RED);
            printStringWC(regNames[i], BLACK, RED);
            printStringWC(": ", BLACK, RED);
            printHexWC(registers[i], BLACK, RED);
            putchar('\n');
      }
      putchar('\n');
}