#include <shell.h>
#include <appManager.h>
#include <buffer.h>
#include <commands.h>
#include <keys.h>
#include <stdint.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

static int checkCommand();
static void shellText();

static t_command commands[] = {{&help, "help"}, {&inforeg, "inforeg"}, {&printmem, "printmem"}, {&time, "time"}, {&cpuInfo, "cpuInfo"}, {&cpuTemp, "cpuTemp"}, {&changeUsername, "changeUsername"}, {0, ""}};

static t_buffer shellBuffer = {{0}, 0};

static char username[BUFFER_SIZE] = "USER";

static int started = 0, availableRemoves = 0, blink=1;

void runShell() {
      if (!started) {
            shellText();  //primera vez q entra tiene q desplegar el texto
            started = 1;
      }
      while (1) {
            char c = getchar();
            if (c != 0) {
                  switch (c) {
                        case CHANGE_SCREEN_0:
                              staticputchar(' ');  //for timer tick
                              changeApplication(calculator);
                              break;
                        case CHANGE_SCREEN_1:
                              break;
                        case ENTER:
                              newLine();
                              checkCommand();
                              cleanBuffer(&shellBuffer);
                              shellText();
                              staticputchar(' ');  //for timer tick
                              availableRemoves = 0;
                              break;
                        case CLEAR_SCREEN:
                              sys_clear();
                              cleanBuffer(&shellBuffer);
                              shellText();
                              availableRemoves = 0;
                              break;
                        case B_SPACE:
                              if (availableRemoves != 0) {
                                    shellBuffer.buffer[--shellBuffer.index] = 0;
                                    availableRemoves--;
                                    staticputchar(' ');  //for timer tick
                                    deletechar();
                              }
                              break;

                        default:
                              if (shellBuffer.index < BUFFER_SIZE) {
                                    shellBuffer.buffer[shellBuffer.index++] = c;
                                    availableRemoves++;
                                    putchar(c);
                              }
                  }
            } else {
                  if(sys_ticksElapsed()%12==0){
                        if(blink){
                              staticputchar('|');
                              blink=0;
                        }
                        else{
                              staticputchar(' ');
                              blink = 1;
                        }
                  }
            }
      }
}

static void shellText() {
      printString(username);
      printString(" $ > ");
}

static int checkCommand() {
      uint32_t cmdIdx, found = 0;
      int error;
      uint64_t mem;
      char arg1[BUFFER_SIZE] = {0};
      char command[BUFFER_SIZE] = {0};
      strtok(shellBuffer.buffer, command, ' ');
      strtok(0, arg1, ' ');
      strtok(0, 0, ' ');

      for (cmdIdx = 0; commands[cmdIdx].command != 0 && !found; cmdIdx++) {
            if (stringcmp(commands[cmdIdx].name, command)) {
                  found = 1;
            }
      }
      if (found) {
            switch (cmdIdx - 1) {
                  case HELP:
                        commands[HELP].command();
                        break;
                  case INFOREG:
                        commands[INFOREG].command();
                        break;
                  case PRINTMEM:
                        mem = strToInt(arg1,&error);
                        if(!error){
                        commands[PRINTMEM].command(mem);
                        }
                        else{
                              printStringLn("Invalid argument for function printmem (must be an integer)");
                        }
                        break;
                  case TIME:
                        commands[TIME].command();
                        break;
                  case CPUINFO:
                        commands[CPUINFO].command();
                        break;
                  case CPUTEMP:
                        commands[CPUTEMP].command();
                        break;
                  case CHANGEUSERNAME:
                        commands[CHANGEUSERNAME].command(arg1);
                        break;
            }
      }

      else {
            printStringLn("Invalid command");
      }

      return found;
}

void changeUsername(char * newUsername) {
      cleanString(username);
      for (int i = 0; newUsername[i]!=0 ; i++)
      {
            username[i]=newUsername[i];
      }
}
