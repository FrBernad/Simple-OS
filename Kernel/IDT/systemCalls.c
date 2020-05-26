#include <systemCalls.h>

//dataTypes
#include <colours.h>

//functions prot
#include <lib.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <timerTick.h>

void sys_inforeg(t_register * registers) {
      getRegisters(registers);
}

uint8_t sys_RTCTime(t_timeInfo tInfo) {
      return getDecimalTimeInfo(tInfo);
}

void sys_cpuInfo(t_cpuInfo * cpuInfo) {
      cpuVendor(cpuInfo->cpuVendor);
      cpuInfo->model = cpuModel();
}

uint8_t sys_temp() {
      return cpuTemp();
      //return 80;
}

void sys_write(char * string, uint8_t lenght){
      for (int i = 0; string[i] != 0 && i < lenght; i++) {
            printCharOnScreen(string[i], BLACK, WHITE, 1);
      }
}

void sys_staticwrite(char * string, uint8_t lenght) {
      for (int i = 0; string[i] != 0 && i < lenght; i++) {
            printCharOnScreen(string[i], BLACK, WHITE, 0);
      }
}

char sys_getchar() {
      return getchar();
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

int sys_ticksElapsed(){
      return ticksElapsed();
}

void sys_changeResources(t_application * app){
      changeScreen(app->screenID);
      changeBuffer(app->appID);
}
