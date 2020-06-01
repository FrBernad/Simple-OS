
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
static void printRegisters(uint64_t * registers);

extern t_queue taskManager;


void exceptionDispatcher(int exception, uint64_t* stackframe, uint64_t * registers) {
      t_application currentProcess;
      queuePeek(&taskManager, &currentProcess);
      stackframe[0] = (uint64_t)currentProcess.app;
      stackframe[3] = (uint64_t)currentProcess.stack;
      switch (exception) {
            case ZERO_EXCEPTION_ID:
                  zero_division();
                  break;

            case INVALID_OPCODE_ID:
                  invalid_op_code();
                  break;
      }
      printRegisters(registers);
}

static void zero_division() {
      printStringLn("Warning: division by zero is undefined");
}

static void invalid_op_code() {
      printStringLn("Invalid Opcode");
}

// rrsp rrbp rrip rrax rrcx rrdx rrbx rrsi rrdi rr8 rr9 rr10 rr11 rr12 rr13 rr14 rr15
static void printRegisters(uint64_t * registers){
      char* regNames[] = {"rsp","rbp","rip","rax", "rcx", "rdx", "rbx", "rsi", "rdi", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
      for (int i = 0; i < REGISTERS; i++) {
            printString(" > ");
            printString(regNames[i]);
            putchar(':');
            printHex(registers[i]);
            putchar('\n');
      }
      putchar('\n');
}