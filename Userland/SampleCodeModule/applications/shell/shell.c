#include <appManager.h>
#include <buffer.h>
#include <commands.h>
#include <registers.h>
#include <keys.h>
#include <shell.h>
#include <stdint.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>
#include <lib.h>

static void initShell();
static void shellText();
static void processCommand();
static void processChar(char c);

static t_command commands[COMMANDS];
static t_buffer shellBuffer = {{0}, 0};
static char username[BUFFER_SIZE] = "USER";
static int blink = 1, started = 0;
static t_registers registers;

//TODO: RIP
//TODO: REVISAR TEMP

//TODO: INVALID OP HACE RQ HAGA INVALID OP

void runShell() {
      if (!started) {
            initShell();
      }
      char c;
      while (1) {
            c=0;
            while(c==0){
                  halt();
                  getRegistersData(registers.data);
                  c = getchar();

                  if (sys_ticksElapsed() % 12 == 0) {
                        blinkCursor(&blink);
                  }
            }
            processChar(c);
      }
}

static void initShell() {
      t_command commandsData[] = {
          {&help, "help", "Shows the list of commands and their use"},
          {&inforeg, "inforeg", "prints the value of all the registers on screen"},
          {&printmem, "printmem", "recieves a pointer and makes a memory dump of 32 bytes on screen"},
          {&time, "time", "prints the current system time on screen"},
          {&cpuInfo, "cpuInfo", "prints the processor brand and model on screen"},
          {&cpuTemp, "cpuTemp", "prints the current processor temperature on screen"},
          {&changeUsername, "changeUsername", "changes the shell prompt username"},
          {&checkZeroException, "checkZeroException", "Triggers a zero division exception"},
          {&checkInvalidOpcodeException, "checkInvalidOpcodeException", "Triggers an invalid opcode exception"},
          {&showArgs, "showArgs", "prints the arguments passed to this command"}};
      for (int i = 0; i < COMMANDS; i++) {
            commands[i].command = commandsData[i].command;
            commands[i].name = commandsData[i].name;
            commands[i].description = commandsData[i].description;
      }

      char* regNames[] = {"rip", "rax", "rcx", "rdx", "rbx", "rsi", "rdi", "rsp", "rbp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
      getRegistersData(registers.data);

      for (int i = 0; i < REGISTERS; i++) {
            strcpy(regNames[i], registers.name[i]);
      }

      shellText();
      started = 1;
}

static void processChar(char c) {
      if (c != 0) {
            staticputchar(' ');  //remove blink
            switch (c) {
                  case CHANGE_SCREEN_0:
                        sys_changeApp();
                        break;
                  case CHANGE_SCREEN_1:
                        break;
                  case CLEAR_SCREEN:
                        sys_clear();
                        cleanBuffer(&shellBuffer);
                        shellText();
                        break;
                  case '\n':
                        putchar('\n');
                        processCommand();
                        cleanBuffer(&shellBuffer);
                        shellText();
                        break;
                  case '\b':
                        if (shellBuffer.index > 0) {
                              shellBuffer.buffer[--shellBuffer.index] = 0;
                              deletechar();
                        }
                        break;

                  default:
                        if (shellBuffer.index < BUFFER_SIZE) {
                              shellBuffer.buffer[shellBuffer.index++] = c;
                              putchar(c);
                        }
            }
      }
}

static void processCommand() {
      int argc = 0;
      char arg1[BUFFER_SIZE] = {0}, arg2[BUFFER_SIZE] = {0}, arg3[BUFFER_SIZE] = {0}, arg4[BUFFER_SIZE] = {0};
      char* argv[MAX_ARGS] = {arg1, arg2, arg3, arg4};
      char command[BUFFER_SIZE] = {0};
      strtok(shellBuffer.buffer, command, ' ');  //parse buffer
      strtok(0, command, ' ');                   //parse buffer
      while (argc < MAX_ARGS && strtok(0, argv[argc], ' ')) {
            argc++;
      };
      strtok(0, 0, ' ');
      for (int i = 0; i < COMMANDS; i++) {
            if (stringcmp(commands[i].name, command) == 0) {
                  commands[i].command(argc, argv);
                  return;
            }
      }
      printStringLn("Invalid command");
}

static void shellText() {
      printStringWC(username, BLACK, WHITE);
      printStringWC(" $ > ", BLACK, WHITE);
}

void changeUsername(int argc, char** argv) {
      if (argc != 1) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      cleanString(username);
      for (int i = 0; argv[0][i] != 0; i++) {
            username[i] = argv[0][i];
      }
}

void help(int argc, char** args) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }

      printStringLn("These shell commands are defined internally.  Type 'help' to see this list.");
      for (int i = 0; i < COMMANDS; i++) {
            printString(" >");
            printString(commands[i].name);
            printString(": ");
            printStringLn(commands[i].description);
      }
      putchar('\n');
}

void inforeg(int argc, char** args) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      for (int i = 0; i < REGISTERS; i++) {
            printString(" > ");
            printString(registers.name[i]);
            putchar(':');
            printHex(registers.data[i]);
            putchar('\n');
      }
      putchar('\n');
}

