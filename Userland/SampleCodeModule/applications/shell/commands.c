#include <RTCTime.h>
#include <commands.h>
#include <cpuInfo.h>
#include <registers.h>
#include <shell.h>
#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

void help() {
      printStringLn("These shell commands are defined internally.  Type 'help' to see this list.");
      printStringLn(" >inforeg: prints the value of all the registers on screen");
      printStringLn(" >printmem: recieves a pointer and makes a memory dump of 32 bytes on screen");
      printStringLn(" >time: prints the current system time on screen");
      printStringLn(" >cpuid: prints the processor brand and model on screen");
      printStringLn(" >temp: prints the current processor temperature on screen");
      printStringLn(" >changeUsername: changes the shell prompt username");
      newLine();
}

void inforeg() {
      t_register registers[REGISTERS];
      sys_inforeg(registers);
      for (int i = 0; i < REGISTERS; i++) {
            printString(" > ");
            printString(registers[i].name);
            putchar(':');
            printHex(registers[i].data);
            newLine();
      }
      newLine();
}

void time() {
      uint8_t hours = sys_RTCTime(HOURS);
      uint8_t mins = sys_RTCTime(MINUTES);
      uint8_t secs = sys_RTCTime(SECONDS);
      printString("Time -> ");
      printInt(hours);
      putchar(':');
      printInt(mins);
      putchar(':');
      printInt(secs);
      newLine();
      newLine();
}

void cpuInfo() {
      char cpuVendor[14] = {0};
      t_cpuInfo cpuInfo = {cpuVendor, 0};
      sys_cpuInfo(&cpuInfo);
      printString(" > CPU Vendor: ");
      printStringLn(cpuInfo.cpuVendor);
      printString(" > CPU model: ");
      printInt(cpuInfo.model);
      newLine();
      newLine();
}

void printmem(uint64_t mem) {
      char byteStr[3] = {'0', '0', 0};
      uint8_t byte;
      printStringLn(" >Data dump:");

      for (int i = 0; i < 32; i++) {
            byte = sys_getMem(mem);
            if (byte <= 0xF) {
                  uintToBase(byte, byteStr + 1, 16);
            } else {
                  uintToBase(byte, byteStr, 16);
            }
            printString("   -[0x");
            printHex(mem++);
            printString("]: ");
            printStringLn(byteStr);
            byteStr[0] = '0';
            byteStr[1] = '0';
            byteStr[2] = 0;
      }
      newLine();
}

void cpuTemp() {
      printString("CPU temp:  ");
      printInt(sys_temp());
      printStringLn("C");
      newLine();
}
