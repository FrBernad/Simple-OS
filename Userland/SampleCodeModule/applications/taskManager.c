#include <taskManager.h>
#include <systemCalls.h>
#include <shell.h>
#include <calculator.h>

#define MAX_PROCESSES 2

static t_PCB processes[MAX_PROCESSES];

void initApps() {
      t_PCB shell = {&runShell, 0, 0, SCREEN_1};
      t_PCB calculator = {&runCalculator, 0, 0, SCREEN_0};
      processes[0] = shell;
      processes[1] = calculator;
      for (int i = 0; i < MAX_PROCESSES; i++) {
            sys_loadApp(&processes[i]);
      }
      sys_run();
}
