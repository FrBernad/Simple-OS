#include <taskManager.h>
#include <systemCalls.h>
#include <shell.h>
#include <calculator.h>
#include <stringLib.h>

#define MAX_PROCESSES 2

static t_PCB processes[MAX_PROCESSES];

//load apps in kernel and forces the first app in queue to run
void initApps() {
      t_PCB shell = {&runShell, 0, 0, 0, SCREEN_1};
      t_PCB calculator = {&runCalculator, 0, 0, 0, SCREEN_0};
      processes[0] = shell;
      processes[1] = calculator;
      int loaded = 0;
      for (int i = 0; i < MAX_PROCESSES; i++) {
            loaded += syscall(LOAD_APP, (uint64_t)&processes[i], 0, 0, 0, 0, 0);
      }
      if(loaded!=0){
            syscall(RUN, 0, 0, 0, 0, 0, 0);
      }
}
