#include <RTCTime.h>
#include <applications.h>
#include <stdint.h>
#include <sysCallDispatcher.h>
#include <systemCalls.h>
#include <stringLib.h>
#include <timerTick.h>
#include <lib.h>
#include <taskManager.h>

#define SYS_GETMEM_ID 0
#define SYS_RTC_TIME_ID 1
#define SYS_TEMP_ID 2
#define SYS_WRITE_ID 3
#define SYS_STATIC_WRITE_ID 4
#define SYS_GETCHAR_ID 5
#define SYS_CLEAR_ID 6
#define SYS_TICKS_ELAPSED_ID 7
#define SYS_CHANGE_APP_ID 8
#define SYS_LOAD_APP_ID 9
#define SYS_RUN_ID 10

uint64_t sysCallDispatcher(t_registers *r) {
      if (r->rax >= 0 && r->rax <= SYSCALLS){
            switch (r->rax) {
                  case SYS_GETMEM_ID:
                        sys_getMem(r->rdi,(uint8_t*)r->rsi);
                        break;

                  case SYS_RTC_TIME_ID:
                        return sys_RTCTime((t_timeInfo)(r->rdi));
                        break;

                  case SYS_TEMP_ID:
                        return sys_temp();
                        break;

                  case SYS_WRITE_ID:
                        sys_write((char *)(r->rdi), (uint8_t)(r->rsi), (t_colour)(r->rdx), (t_colour)(r->r10));
                        break;

                  case SYS_STATIC_WRITE_ID:
                        sys_staticwrite((char *)(r->rdi), (uint8_t)(r->rsi), (t_colour)(r->rdx), (t_colour)(r->r10));
                        break;

                  case SYS_GETCHAR_ID:
                        return sys_getchar();
                        break;

                  case SYS_CLEAR_ID:
                        sys_clear();
                        break;

                  case SYS_TICKS_ELAPSED_ID:
                        return ticksElapsed();
                        break;

                  case SYS_CHANGE_APP_ID:
                        sys_changeProcess();
                        break;

                  case SYS_LOAD_APP_ID:
                        addProcess((t_application*)r->rdi);
                        break;

                  case SYS_RUN_ID:
                        sys_forceStart();
                        break;
            }
      }

      return 0;
}
