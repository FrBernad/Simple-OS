// #include <shell.h>
// #include <commands.h>
// #include <stringLib.h>
// #include <buffer.h>
// #include <stdint.h>
// #include <utils.h>
// #include <keys.h>
// #include <screens.h>

// // static int checkCommand();
// // static void getArg(char* arg, char * buffer);


// // static t_command commands[] = {{&help, "help"}, {&inforeg, "inforeg"}, {&printmem, "printmem"}, {&time, "time"}, {&cpuInfo, "cpuInfo"}, {&temp, "temp"}, {0, ""}};

// static t_buffer shellBuffer={{0},0};

// void runShell(){
//     //while(1){
//         char c = getchar();
//         // if(c == CHANGE_SCREEN_1){
//         //       //changeScreen(SCREEN_1);
//         //       break;
//         // }
//         // if (c != 0) {
//         //       switch (c) {
//         //             case ENTER:
//         //                   newLine();
//         //                 //   checkCommand();
//         //                   break;

//         //             case B_SPACE:
//         //                   shellBuffer.buffer[shellBuffer.index] = 0;
//         //                   if (shellBuffer.index > 0) {
//         //                         shellBuffer.index--;
//         //                   }
//         //                   deletechar();
//         //                   break;

//         //             default:
//         //                   shellBuffer.buffer[shellBuffer.index++]=c;
//         //                   putchar(c);
//         //       }
//         // }
//   //  }
// }

// // static int checkCommand() {
// //       uint32_t command, found = 0;
// //       char arg[BUFFER_SIZE] = {0};

// //       if (shellBuffer.buffer[0] == 0) {
// //             return 0;
// //       }

// //       for (command = 0; commands[command].command != 0 && !found; command++) {
// //             if (stringcmp(commands[command].name, shellBuffer.buffer)) {
// //                   found = 1;
// //             }
// //       }
// //       if (found) {
// //             switch (command - 1) {
// //                   case HELP:
// //                         commands[HELP].command();
// //                         break;
// //                   case INFOREG:
// //                         commands[INFOREG].command();
// //                         break;
// //                   case PRINTMEM:
// //                         getArg(arg, shellBuffer.buffer);
// //                         commands[PRINTMEM].command(strToInt(arg));
// //                         break;
// //                   case TIME:
// //                         commands[TIME].command();
// //                         break;
// //                   case CPUINFO:
// //                         commands[CPUINFO].command();
// //                         break;
// //                   case TEMP:
// //                         commands[TEMP].command();
// //                         break;
// //             }
// //       }

// //       else {
// //             printString("Invalid command",1);
// //       }

// //       return found;
// // }

// // static void getArg(char* arg, char * buffer) {
// //       int i;

// //       for (i = 0; i < BUFFER_SIZE && buffer[i] == ' ' && buffer[i] != 0; i++);

// //       for (; i < BUFFER_SIZE && buffer[i] != ' ' && buffer[i] != 0; i++);

// //       for (; i < BUFFER_SIZE && buffer[i] == ' ' && buffer[i] != 0; i++);

// //       for (int j = 0; i < BUFFER_SIZE && buffer[i] != 0 && buffer[i] != ' ';) {
// //             arg[j++] = buffer[i++];
// //       }
// // }