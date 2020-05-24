#include <systemCalls.h>
#include <registers.h>
#include <colours.h>
#include <clock.h>
#include <utils.h>
#include <lib.h>
#include <videoDriver.h>
#include <keyboardDriver.h>


void sys_help() {
      sys_printString("These shell commands are defined internally.  Type 'help' to see this list.", 1);
      sys_printString(" >inforeg: prints the value of all the registers on screen", 1);
      sys_printString(" >printmem: recieves a pointer and makes a memory dump of 32 bytes on screen", 1);
      sys_printString(" >time: prints the current system time on screen", 1);
      sys_printString(" >cpuid: prints the processor brand and model on screen", 1);
      sys_printString(" >temp: prints the current processor temperature on screen", 1);
}

//todo: print registers, done in assembly
void sys_inforeg() {
      t_register registers[REGISTERS];
      getRegisters(registers);

      for (int i = 0; i < REGISTERS; i++) {
            sys_printString(" > ", 0);
            sys_printString(registers[i].name, 0);
            sys_putchar(':');
            sys_printNum(registers[i].data, 16);
            sys_newLine();
      }
}

//todo: recieves memory direction and prints 32 bytes after
void sys_printmem(uint64_t mem) {
      sys_printString(" > Data at memory ", 0);
      sys_printNum(mem, 16);
      sys_printString(": ", 0);
      // sys_printNum(getMem(mem),0);
      sys_newLine();
}

//todo: desplays system time
void sys_time() {
      uint8_t hours = getDecimalTimeInfo(HOURS);
      uint8_t mins = getDecimalTimeInfo(MINUTES);
      uint8_t secs = getDecimalTimeInfo(SECONDS);
      sys_printString("Time -> ", 0);
      sys_printNum(hours, 10);
      sys_putchar(':');
      sys_printNum(mins, 10);
      sys_putchar(':');
      sys_printNum(secs, 10);
      sys_newLine();
}

char sys_getchar() {
      return getChar();
}

//todo: shows processor model and brand
void sys_cpuInfo() {
      char buffer[15];
      sys_printString(" > CPU Vendor: ", 0);
      sys_printString(cpuVendor(buffer), 1);
      sys_printString(" > CPU model: ", 0);
      sys_printNum(cpuModel(), 10);
      sys_newLine();
}

//todo: shows processor temp
void sys_temp() {
      sys_printString(" > CPU temp: ", 0);
      sys_printNum(cpuTemp(), 16);
      sys_newLine();
}

int BGColour = BLACK;
int FontColour = WHITE;

void sys_putchar(char c) {
      printCharOnScreen(c, BGColour, FontColour, 1);
}

void sys_printString(char *str, uint8_t newLine) {
      for (uint8_t i = 0; str[i] != 0; i++) {
            sys_putchar(str[i]);
      }

      if (newLine) {
            sys_newLine();
      }
}

void sys_printNum(uint64_t num, uint8_t base) {
      char buffer[10];
      uintToBase(num, buffer, base);
      sys_printString(buffer, 0);
}

void sys_deletechar() {
      removeCharFromScreen();
}

void sys_newLine() {
      changeLineOnScreen();
}

void sys_clearLine() {
      clearLineOnScreen();
}

void sys_clear() {
      clearScreen();
}

uint8_t sys_stringcmp(char *str1, char *str2) {
      uint8_t i;
      if (*str1 == 0 || *str2 == 0) {
            return 0;
      }
      for (i = 0; str1[i] != 0 && str2[i] != 0; i++) {
            if (str1[i] != str2[i])
                  return 0;
      }
      return 1;
}
