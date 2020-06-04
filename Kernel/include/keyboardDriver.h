#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <screens.h>

void keyboardHandler();
char getchar();
void changeBuffer(t_screenID screen);
void runProcess();

#endif