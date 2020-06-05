#include <stringLib.h>
#include <taskManager.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6
#define REGISTERS 16

static void zero_division();
static void invalid_op_code();
static void printRegisters(uint64_t* registers);

static char* regNames[] = {"R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ",
                           "R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
                           "RAX: ", "RIP: ", "RSP: "};

//Maneja la excepcion recibida y reinicia el proceso actual
void exceptionDispatcher(int exception, void* stackframe) {
      switch (exception) {
            case ZERO_EXCEPTION_ID:
                  zero_division();
                  break;

            case INVALID_OPCODE_ID:
                  invalid_op_code();
                  break;
      }
      printRegisters(stackframe);
      putchar('\n');
      resetCurrentProcess();
}

static void zero_division() {
      printStringWC("Warning: division by zero is undefined\n", BLACK, RED);
}

static void invalid_op_code() {
      printStringWC("Invalid Opcode\n", BLACK, RED);
}

static void printRegisters(uint64_t* registers) {

      for (int i = 0; i < REGISTERS; i++) {
            printStringWC(regNames[i],BLACK,RED);
            printHexWC(registers[i],BLACK,RED);
            putchar('\n');
      }
      printStringWC(regNames[REGISTERS], BLACK, RED);
      printHexWC(registers[15+3], BLACK, RED);  //print rsp value from interrupt stackframe
}