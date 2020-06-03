#include <systemCalls.h>

//dataTypes
#include <colours.h>

//functions prot
#include <lib.h>
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <timerTick.h>

//task Manager
#include <taskManager.h>
#include <staticQueue.h>

extern t_queue taskManager;

uint8_t sys_RTCTime(t_timeInfo tInfo) {
      return getDecimalTimeInfo(tInfo);
}

int sys_temp() {
      return cpuTemp();
}

void sys_write(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour){
      for (int i = 0; string[i] != 0 && i < lenght; i++) {
            if (string[i] == '\n') {
                  changeLineOnScreen();
            } else if (string[i] == '\b'){
                  removeCharFromScreen();
            } else {
                  printCharOnScreen(string[i], bgColour, fontColour, 1);
            }
      }
}

void sys_staticwrite(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour) {
      for (int i = 0; string[i] != 0 && i < lenght; i++) {
            printCharOnScreen(string[i], bgColour, fontColour, 0);
      }
}

char sys_getchar() {
      return getchar();
}

void sys_clear() {
      clearScreen();
}

