
#include <applications.h>
#include <interrupts.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <taskManager.h>
#include <utils.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6

static void zero_division();
static void invalid_op_code();

extern t_queue taskManager;

static t_application currentProcess;

void exceptionDispatcher(int exception, uint64_t* stackframe) {
      printStringLn("Warning: division by zero is undefined");
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
}

static void zero_division() {
      printStringLn("Warning: division by zero is undefined");
      //   inforeg();
}

static void invalid_op_code() {
      printStringLn("Invalid Opcode");
      // inforeg();
}
