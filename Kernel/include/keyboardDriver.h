#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <applications.h>

void keyboardHandler();
char getchar();
void changeBuffer(t_applicationID app);

#endif