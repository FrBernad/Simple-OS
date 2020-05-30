#include <RTCTime.h>
#include <commands.h>
#include <cpuInfo.h>
#include <registers.h>
#include <shell.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>
#include <lib.h>

static void memToString(char * buffer,uint8_t * mem, int bytes);


void time(int argc, char** args) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      uint8_t hours = sys_RTCTime(HOURS);
      uint8_t mins = sys_RTCTime(MINUTES);
      uint8_t secs = sys_RTCTime(SECONDS);
      printString(" >Current time: ");
      printInt(hours);
      putchar(':');
      printInt(mins);
      putchar(':');
      printInt(secs);
      putchar('\n');
      putchar('\n');
}

void cpuInfo(int argc, char** args) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      char vendor[13] = {0};
      t_cpuInfo cpuInfo = {vendor, 0};
      cpuVendor(cpuInfo.cpuVendor);
      cpuInfo.model=cpuModel();
      printString(" > CPU Vendor: ");
      printStringLn(cpuInfo.cpuVendor);
      printString(" > CPU model: ");
      printInt(cpuInfo.model);
      putchar('\n');
      putchar('\n');
}

void printmem(int argc, char** args) {
      if (argc != 1) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }

      int error = 0;
      uint64_t memDir = strToInt(args[0], &error);
      if (error) {
            printStringLn("Invalid argument for function printmem (must be an integer).");
            putchar('\n');
            return;
      }

      int bytes=32;

      uint8_t memData[bytes];
      sys_getMem(memDir,memData);

      char byteStr[bytes*2];
      memToString(byteStr,memData,bytes);

      printString(" >Data dump:");
      for (int i = 0; i < 32; i++) {
            if(i%4==0){
            putchar('\n');
            printString("   -[0x");
            printHex(memDir);
            printString("]: ");
            memDir+=4;
            }
            if (i%2 == 0) {
                  putcharWC(byteStr[i],BLACK,BLUE);
                  putcharWC(byteStr[i + 1], BLACK, BLUE);
                  putchar(' ');
            }
            else{
                  putchar(byteStr[i]);
                  putchar(byteStr[i + 1]);
                  putchar(' ');
            }
      }
      putchar('\n');
}

void cpuTemp(int argc, char** args) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      printString("CPU temp:  ");
      printInt(sys_temp());
      printStringLn("C");
      putchar('\n');
}

void checkZeroException(int argc, char** args) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      int a = 0;
      int b = 20 / a;
      if (b == 0) {
      }
}

void checkInvalidOpcodeException(int argc, char** args) {
      if (argc != 0) {
            printStringLn("Invalid ammount of arguments.");
            putchar('\n');
            return;
      }
      __asm__("ud2");  //https://mudongliang.github.io/x86/html/file_module_x86_id_318.html
}

void showArgs(int argc, char** args){
      for (int i = 0; i < argc && i < MAX_ARGS; i++)
      {
            printString("arg[");
            printInt(i);
            printString("]=");
            printStringLn(args[i]);
      }
}

static void memToString(char* buffer, uint8_t* mem, int bytes){
      for (int i = 0; i < bytes*2; i++)
      {
            if (mem[i] <= 0xF) {
                  buffer[i]='0';
                  uintToBase(mem[i], buffer+ i + 1, 16);
            } else {
                  uintToBase(mem[i], buffer + i, 16);
            }
      }
}
