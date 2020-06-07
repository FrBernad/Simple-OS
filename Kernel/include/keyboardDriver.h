#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <screens.h>
#include <stdint.h>

void keyboardHandler(uint64_t rsp);
char getchar();
void changeBuffer(t_screenID screen);
void runProcess();
uint64_t* getSnapshot();

#endif