#include <appManager.h>
#include <applications.h>
#include <calculator.h>
#include <shell.h>
#include <systemCalls.h>

static t_application applications[MAX_APPS];

void initApps() {
      t_application shell = {&runShell, SCREEN_1};
      t_application calculator = {&runCalculator, SCREEN_0};
      applications[0] = shell;
      applications[1] = calculator;
      for (int i = 0; i < MAX_APPS; i++) {
            sys_loadApp(&applications[i]);
      }
      sys_run();
}
