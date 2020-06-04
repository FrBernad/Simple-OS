#include <taskManager.h>
#include <buffer.h>
#include <commands.h>
#include <keys.h>
#include <lib.h>
#include <registers.h>
#include <shell.h>
#include <stdint.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

static void initShell();
static void shellText();
static void processCommand();
static void processChar(char c);

static t_command commands[COMMANDS];
static t_buffer shellBuffer = {{0}, 0};
static char username[BUFFER_SIZE] = "USER";
static t_registers registers;

//TODO: checkear kill process que vuelva a resetar proceso
//TODO: syscall exit al final runshel y calc
//TODO: cambiar halt y blink a kernel driver PREGUNTAR A NICO
//TODO: REVISAR TEMP
//TODO: achicar syscalls
//TODO: hacer lo de inforeg con una tecla

void runShell() {
      initShell();
      char c;
      while (1) {
            c = getchar();
            processChar(c);
      }
    //  sys_exit();
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

      cleanBuffer(&shellBuffer);
      shellText();
}

static void processChar(char c) {
      if (c != 0) {
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
      strtok(0, 0, ' ');
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
