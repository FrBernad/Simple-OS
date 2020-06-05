#include <shell.h>
#include <commands.h>
#include <keys.h>
#include <lib.h>
#include <registers.h>
#include <stdint.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

static void initShell(t_shellData* shellData);
static void shellText(t_shellData* shellData);
static void processCommand(t_shellData* shellData);
static void processChar(char c, t_shellData* shellData);

static char* regNames[] = {"RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RDI: ", "RSI: ", "R8: ", "R9: ", "R10: ", "R11: ", "R12: ", "R13: ", "R14: ", "R15: "};


//TODO: CHECKEAR TODOS LOS PARAMETROS RECIBIDOS POR SYSCALLS Y FUNCIONES POR EJEMPLO EN LOAD PROCESS RECIBIR UNA SCREENQ  NO EXISTE
//FIXME: cambiar halt y blink a kernel driver PREGUNTAR A NICO

void runShell() {
      t_shellData shellData;
      initShell(&shellData);
      char c;
      while (1) {
            c = getchar();
            processChar(c,&shellData);
      }
      syscall(EXIT, 0, 0, 0, 0, 0, 0);
}


//inicia la shell y todas sus estructuras 
static void initShell(t_shellData* shellData) {
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
            shellData->commands[i].command = commandsData[i].command;
            shellData->commands[i].name = commandsData[i].name;
            shellData->commands[i].description = commandsData[i].description;
      }

      cleanBuffer(&shellData->buffer);
      strcpy("USER", shellData->username);
      shellText(shellData);
}

//procesa el caracter recibido actua segun el mismo
static void processChar(char c, t_shellData * shellData) {
      if (c != 0) {
            switch (c) {
                  case CHANGE_SCREEN_0:
                        sys_changeApp();
                        break;
                  case CHANGE_SCREEN_1:
                        break;
                  case CLEAR_SCREEN:
                        syscall(CLEAR,0,0,0,0,0,0);
                        cleanBuffer(&shellData->buffer);
                        shellText(shellData);
                        break;
                  case '\n':
                        putchar('\n');
                        processCommand(shellData);
                        cleanBuffer(&shellData->buffer);
                        shellText(shellData);
                        break;
                  case '\b':
                        if (shellData->buffer.index > 0) {
                              shellData->buffer.buffer[--shellData->buffer.index] = 0;
                              deletechar();
                        }
                        break;

                  default:
                        if (shellData->buffer.index < BUFFER_SIZE) {
                              shellData->buffer.buffer[shellData->buffer.index++] = c;
                              putchar(c);
                        }
            }
      }
}

//procesa el comando, tokenizando lo ingresado.
static void processCommand(t_shellData * shellData) {
      int argc = 0;
      char arg1[BUFFER_SIZE] = {0}, arg2[BUFFER_SIZE] = {0}, arg3[BUFFER_SIZE] = {0}, arg4[BUFFER_SIZE] = {0};
      char* argv[MAX_ARGS] = {arg1, arg2, arg3, arg4};
      char command[BUFFER_SIZE] = {0};
      strtok(0, 0, ' ');
      strtok(shellData->buffer.buffer, command, ' ');    //parse buffer
      strtok(0, command, ' ');                           //parse buffer
      while (argc < MAX_ARGS && strtok(0, argv[argc], ' ')) {
            argc++;
      };
      strtok(0, 0, ' ');
      for (int i = 0; i < COMMANDS; i++) {
            if (stringcmp(shellData->commands[i].name, command) == 0) {
                  shellData->commands[i].command(argc, argv, shellData);
                  return;
            }
      }
      printStringLn("Invalid command");
}

static void shellText(t_shellData * shellData) {
      printStringWC(shellData->username, BLACK, WHITE);
      printStringWC(" $ > ", BLACK, WHITE);
}

void inforeg(int argc, char** args, t_shellData* shellData) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      uint64_t* regData = (uint64_t*)syscall(INFOREG, 0, 0, 0, 0, 0, 0);
      for (int i = 0; i < REGISTERS; i++) {
            printString(" > ");
            printString(regNames[i]);
            printHex(regData[i]);
            putchar('\n');
      }
      putchar('\n');
}

void changeUsername(int argc, char** argv, t_shellData * shellData) {
      if (argc != 1) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      cleanString(shellData->username);
      strcpy(argv[0],shellData->username);
}

void help(int argc, char** args, t_shellData * shellData) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }

      printStringLn("These shell commands are defined internally.  Type 'help' to see this list.");
      for (int i = 0; i < COMMANDS; i++) {
            printString(" >");
            printString(shellData->commands[i].name);
            printString(": ");
            printStringLn(shellData->commands[i].description);
      }
      putchar('\n');
}
