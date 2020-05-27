#include <RTCTime.h>
#include <applications.h>
#include <cpuInfo.h>
#include <registers.h>
#include <stdint.h>
#include <sysCallDispatcher.h>
#include <systemCalls.h>

#define SYS_INFOREG_ID 0
#define SYS_GETMEM_ID 1
#define SYS_RTC_TIME_ID 2
#define SYS_CPUINFO_ID 3
#define SYS_TEMP_ID 4
#define SYS_WRITE_ID 5
#define SYS_STATIC_WRITE_ID 6
#define SYS_GETCHAR_ID 7
#define SYS_DELETE_CHAR_ID 8
#define SYS_CLEAR_ID 9
#define SYS_TICKS_ELAPSED_ID 10
#define SYS_CHANGE_RESOURCES_ID 11

uint64_t sysCallDispatcher(registers *r) {
      if (r->rax >= 0 && r->rax <= SYSCALLS)
            switch (r->rax) {
                  case SYS_INFOREG_ID:
                        sys_inforeg((t_register *)r->rdi);
                        break;

                  case SYS_GETMEM_ID:
                        return sys_getMem(r->rdi);
                        break;

                  case SYS_RTC_TIME_ID:
                        return sys_RTCTime((t_timeInfo)(r->rdi));
                        break;

                  case SYS_CPUINFO_ID:
                        sys_cpuInfo((t_cpuInfo *)(r->rdi));
                        break;

                  case SYS_TEMP_ID:
                        return sys_temp();
                        break;

                  case SYS_WRITE_ID:
                        sys_write((char *)(r->rdi), (uint8_t)(r->rsi), (t_colour)(r->rdx), (t_colour)(r->rcx));
                        break;

                  case SYS_STATIC_WRITE_ID:
                        sys_staticwrite((char *)(r->rdi), (uint8_t)(r->rsi), (t_colour)(r->rdx), (t_colour)(r->rcx));
                        break;

                  case SYS_GETCHAR_ID:
                        return sys_getchar();
                        break;

                  case SYS_DELETE_CHAR_ID:
                        sys_deletechar();
                        break;

                  case SYS_CLEAR_ID:
                        sys_clear();
                        break;

                  case SYS_TICKS_ELAPSED_ID:
                        return sys_ticksElapsed();
                        break;

                  case SYS_CHANGE_RESOURCES_ID:
                        sys_changeResources((t_application *)r->rdi);
                        break;
            }
            
      return 0;
}
