#include <RTCTime.h>
#include <applications.h>
#include <cpuInfo.h>
#include <registers.h>
#include <stdint.h>
#include <sysCallDispatcher.h>
#include <systemCalls.h>

// #define MAX_FUNCS 64

// static void (*syscalls[MAX_FUNCS])() = {&sys_putchar, &sys_printString, &sys_printNum, &sys_deleteChar,&sys_clear,
// &sys_clearLine, &sys_newLine, &sys_stringcmp, &sys_help, &sys_inforeg, &sys_printmem, &sys_time, &sys_cpuInfo, &sys_temp, &sys_getchar};

//static void (*syscalls[MAX_FUNCS])(registers * r) = {0};

//TODO: STRCMP CAMBIAR SI ES SYS O NO

uint64_t sysCallDispatcher(registers *r) {
      if (r->rax >= 0 && r->rax <= SYSCALLS)
            switch (r->rax) {
                  case 0:
                        sys_inforeg((t_register *)r->rdi);
                        break;

                  case 1:
                        return sys_getMem(r->rdi);
                        break;

                  case 2:
                        return sys_RTCTime((t_timeInfo)(r->rdi));
                        break;

                  case 3:
                        sys_cpuInfo((t_cpuInfo *)(r->rdi));
                        break;

                  case 4:
                        return sys_temp();
                        break;

                  case 5:
                        sys_write((char *)(r->rdi), (uint8_t)(r->rsi));
                        break;

                  case 6:
                        sys_staticwrite((char *)(r->rdi), (uint8_t)(r->rsi));
                        break;

                  case 7:
                        return sys_getchar();
                        break;

                  case 8:
                        sys_deletechar();
                        break;

                  case 9:
                        sys_newLine();
                        break;

                  case 10:
                        sys_clearLine();
                        break;

                  case 11:
                        sys_clear();
                        break;

                  case 12:
                        return sys_ticksElapsed();
                        break;

                  case 13:
                        sys_changeResources((t_application *)r->rdi);
                        break;
            }
            
      return 0;
}
