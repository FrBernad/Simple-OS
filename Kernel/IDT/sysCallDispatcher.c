#include <sysCallDispatcher.h>
#include <systemCalls.h>
#include <stdint.h>

// #define MAX_FUNCS 64

// static void (*syscalls[MAX_FUNCS])() = {&sys_putchar, &sys_printString, &sys_printNum, &sys_deleteChar,&sys_clear, 
// &sys_clearLine, &sys_newLine, &sys_stringcmp, &sys_help, &sys_inforeg, &sys_printmem, &sys_time, &sys_cpuInfo, &sys_temp, &sys_getchar};

//static void (*syscalls[MAX_FUNCS])(registers * r) = {0};

uint64_t sysCallDispatcher(registers *r) {
      if (r->rax >= 0 && r->rax <= SYSCALLS)
            switch (r->rax) {
                  case 0:
                        sys_putchar((char)r->rdi);
                        break;

                  case 1:
                        sys_printString((char*)r->rdi,(uint8_t)r->rsi);
                        break;

                  case 2:
                        sys_printNum(r->rdi, r->rsi);
                        break;

                  case 3:
                        sys_deletechar();
                        break;
                  case 4:
                        return sys_getchar();
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
                        sys_stringcmp((char *)r->rdi,(char *)r->rsi);
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
            return 0;
}

