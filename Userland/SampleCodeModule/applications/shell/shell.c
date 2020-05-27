#include <appManager.h>
#include <buffer.h>
#include <commands.h>
#include <keys.h>
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
static int blink = 1;

void runShell() {
      initShell();
      while (1) {
            if (sys_ticksElapsed() % 12 == 0) {
                  blinkCursor(&blink);
            }
            char c = getchar();
            processChar(c);
      }
}

static void initShell(){
      t_command commandsData[] = {{&help, "help"}, {&inforeg, "inforeg"}, {&printmem, "printmem"},
       {&time, "time"}, {&cpuInfo, "cpuInfo"}, {&cpuTemp, "cpuTemp"}, 
       {&changeUsername, "changeUsername"}, {&checkZeroException, "checkZeroException"},
        {&checkInvalidOpcodeException, "checkInvalidOpcodeException"}, {&showArgs, "showArgs"}};
      for (int i = 0; i < COMMANDS; i++) {
            commands[i].command = commandsData[i].command;
            commands[i].name = commandsData[i].name;
      }
      shellText();
}

static void shellText() {
      printString(username);
      printString(" $ > ");
}

static void processCommand() {
      int argc = 0;
      char arg1[BUFFER_SIZE] = {0}, arg2[BUFFER_SIZE] = {0}, arg3[BUFFER_SIZE] = {0}, arg4[BUFFER_SIZE] = {0};
      char * argv[MAX_ARGS] = {arg1,arg2,arg3,arg4};
      char command[BUFFER_SIZE] = {0};
      strtok(shellBuffer.buffer, command, ' ');  //parse buffer
      while (argc < MAX_ARGS && strtok(0, argv[argc], ' ')) {
            argc++;
      };
      strtok(0, 0, ' ');
      for (int i = 0; i < COMMANDS; i++) {
            if (stringcmp(commands[i].name, command)) {
                commands[i].command(argc,argv);
                return;
            }
      }
      printStringLn("Invalid command");
}

static void processChar(char c){
      if (c != 0) {
            staticputchar(' ');  //remove blink
            switch (c) {
                  case CHANGE_SCREEN_0:
                        changeApplication(calculator);
                        break;
                  case CHANGE_SCREEN_1:
                        break;
                  case ENTER:
                        putchar('\n');
                        processCommand();
                        cleanBuffer(&shellBuffer);
                        shellText();
                        break;
                  case CLEAR_SCREEN:
                        sys_clear();
                        cleanBuffer(&shellBuffer);
                        shellText();
                        break;
                  case B_SPACE:
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
