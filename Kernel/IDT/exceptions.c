
#include <registers.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6

static void zero_division();
static void invalid_op_code();

void exceptionDispatcher(int exception) {
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
      inforeg();
}

static void invalid_op_code() {
      printStringLn("Warning: division by zero is undefined");
      inforeg();
}
