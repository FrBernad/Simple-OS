#include <systemCallHandler.h>
#include <clock.h>
#include <lib.h>
#include <registers.h>
#include <colours.h>
#include <font.h>
#include <stdint.h>
#include <utils.h>

#define STDOUT 1
#define STDERR 2
#define MAX_FUNCS 64

static void sys_help();
static void sys_inforeg();
static void sys_printmem(uint64_t mem);
static void sys_time();
static void sys_cpuInfo();
static void sys_temp();
static void sys_clearLine();
static void sys_deletechar();
static void sys_printString(char * str, uint8_t newLine);
static void sys_printNum(uint64_t num, uint8_t base);
static void sys_newLine();
static uint8_t sys_stringcmp(char *str1, char *str2);

// static void (*syscalls[MAX_FUNCS])() = {&sys_putchar, &sys_printString, &sys_printNum, &sys_deleteChar,&sys_clear, 
// &sys_clearLine, &sys_newLine, &sys_stringcmp, &sys_help, &sys_inforeg, &sys_printmem, &sys_time, &sys_cpuInfo, &sys_temp, &sys_getchar};

//static void (*syscalls[MAX_FUNCS])(registers * r) = {0};

void systemCallHandler(registers *r) {
      if (r->rax > 0 && r->rax <= MAX_FUNCS)
            switch (r->rax) {
                  case 0:
                        sys_putchar(r->rdi);
                        break;

                  case 1:
                        sys_printString(r->rdi, r->rsi);
                        break;

                  case 2:
                        sys_printNum(r->rdi, r->rsi);
                        break;

                  case 3:
                        sys_deleteChar();
                        break;
                  case 4:
                        sys_getchar();
                        break;
                  case 5:
                        sys_clear();
                        break;
                  case 6:
                        sys_clearLine();
                        break;
                  case 7:
                        sys_newLine();
                        break;
                  case 8:
                        sys_stringcmp(r->rdi, r->rsi);
                        break;
                  case 9:
                        sys_help();
                        break;
                  case 10:
                        sys_inforeg();
                        break;
                  case 11:
                        sys_printmem(r->rdi);
                        break;

                  case 12:
                        sys_time();
                        break;

                  case 13:
                        sys_cpuInfo();
                        break;

                  case 14:
                        sys_temp();
                        break;
            }
}

static void sys_help() {
      sys_printString("These shell commands are defined internally.  Type 'help' to see this list.",1);
      sys_printString(" >inforeg: prints the value of all the registers on screen",1);
      sys_printString(" >printmem: recieves a pointer and makes a memory dump of 32 bytes on screen",1);
      sys_printString(" >time: prints the current system time on screen",1);
      sys_printString(" >cpuid: prints the processor brand and model on screen",1);
      sys_printString(" >temp: prints the current processor temperature on screen",1);
}

//todo: print registers, done in assembly
static void sys_inforeg() {
      t_register registers[REGISTERS];
      getRegisters(registers);

      for (int i = 0; i < REGISTERS; i++) {
            sys_printString(" > ",0);
            sys_printString(registers[i].name,0);
            sys_putchar(':',0);
            sys_printNum(registers[i].data,16);
            sys_newLine();
      }
}

//todo: recieves memory direction and prints 32 bytes after
static void sys_printmem(uint64_t mem) {
      sys_printString(" > Data at memory ",0);
      sys_printNum(mem,16);
      sys_printString(": ",0);
      sys_printNum(getMem(mem),0);
      sys_newLine();
}

//todo: desplays system time
static void sys_time() {
      uint8_t hours = getDecimalTimeInfo(HOURS);
      uint8_t mins = getDecimalTimeInfo(MINUTES);
      uint8_t secs = getDecimalTimeInfo(SECONDS);
      sys_printString("Time -> ",0);
      sys_printNum(hours,10);
      sys_putchar(':');
      sys_printNum(mins,10);
      sys_putchar(':');
      sys_printNum(secs,10);
      sys_newLine();
}

//todo: shows processor model and brand
static void sys_cpuInfo() {
      char buffer[15];
      sys_printString(" > CPU Vendor: ",0);
      sys_printString(cpuVendor(buffer),1);
      sys_printString(" > CPU model: ",0);
      sys_printNum(cpuModel(), 10);
      sys_newLine();
}

//todo: shows processor temp
static void sys_temp() {
      sys_printString(" > CPU temp: ",0);
      sys_printNum(cpuTemp(),16);
      sys_newLine();
}

static int BGColour = BLACK;
static int FontColour = WHITE;

static void sys_putchar(char c) {
      printCharOnScreen(c, BGColour, FontColour, 1);
}

static void sys_printString(char * str, uint8_t newLine) {
      for (uint8_t i = 0; str[i] != 0; i++) {
            sys_putchar(str[i]);
      }
}

static void sys_printNum(uint64_t num, uint8_t base) {
      char buffer[10];
      uintToBase(num, buffer, base);
      sys_printString(buffer,0);
}

static void sys_clearLine() {
      clearLineOnScreen();
}

static void sys_deletechar() {
      removeCharFromScreen();
}


static void sys_clear() {
      clearScreen();
}

static void sys_newLine() {
      changeLineOnScreen();
}

static uint8_t sys_stringcmp(char *str1, char *str2) {
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
