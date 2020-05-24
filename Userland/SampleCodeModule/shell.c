#include <shell.h>
#include <commands.h>
#include <buffer.h>
#include <stdint.h>
#include <keys.h>
#include <screens.h>

static t_command commands[] = {{&help, "help"}, {&inforeg, "inforeg"}, {&printmem, "printmem"}, {&time, "time"}, {&cpuid, "cpuid"}, {&temp, "temp"}, {0, ""}};

static t_buffer shellCommand[BUFFER_SIZE]={0};

void runConsole(){
    while(1){
        uint8_t c = getchar();
        if(c == CHANGE_SCREEN_1){
              changeScreen(SCREEN_1);
              break;
        }
        switch (c) {
              case ENTER:
                    newLine();
                    checkCommand();
                    break;

              case B_SPACE:
                    deletechar();
                    break;

              default:
                    putchar(c);
        }
    }
}

static int checkCommand() {
      uint32_t command, found = 0;
      char arg[BUFFER_SIZE] = {0};

      if (currentBuffer->buffer[0] == 0) {
            return 0;
      }

      for (command = 0; commands[command].command != 0 && !found; command++) {
            if (stringcmp(commands[command].name, currentBuffer->buffer)) {
                  found = 1;
            }
      }
      if (found) {
            switch (command - 1) {
                  case HELP:
                        commands[HELP].command();
                        break;
                  case INFOREG:
                        commands[INFOREG].command();
                        break;
                  case PRINTMEM:
                        getArg(arg, currentBuffer->buffer);
                        commands[PRINTMEM].command(strToInt(arg));
                        break;
                  case TIME:
                        commands[TIME].command();
                        break;
                  case CPUID:
                        commands[CPUID].command();
                        break;
                  case TEMP:
                        commands[TEMP].command();
                        break;
            }
      }

      else {
            printStringLn("Invalid command");
      }

      return found;
}

static void getArg(char* arg, char * buffer) {
      int i;
      for (i = 0; i < BUFFER_SIZE && buffer[i] == ' ' && buffer[i] != 0; i++)
            ;

      for (; i < BUFFER_SIZE && buffer[i] != ' ' && buffer[i] != 0; i++)
            ;

      for (; i < BUFFER_SIZE && buffer[i] == ' ' && buffer[i] != 0; i++)
            ;

      for (int j = 0; i < BUFFER_SIZE && buffer[i] != 0 && buffer[i] != ' ';) {
            arg[j++] = buffer[i++];
      }
}