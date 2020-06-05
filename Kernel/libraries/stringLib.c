#include <stringLib.h>
#include <videoDriver.h>
#include <utils.h>

void sys_write(char* string, uint8_t lenght, t_colour bgColour, t_colour fontColour) {
      for (int i = 0; string[i] != 0 && i < lenght; i++) {
            if (string[i] == '\n') {
                  changeLineOnScreen();
            } else if (string[i] == '\b') {
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

void printString(char * str) {
      sys_write(str,strlen(str),BLACK,WHITE);
}

void printStringWC(char* str, t_colour bgColour, t_colour fontColour) {
      sys_write(str, strlen(str), bgColour, fontColour);
}

void printStringLn(char* str) {
      printString(str);
      putchar('\n');
}

void putchar(char c){
      sys_write(&c, 1, BLACK, WHITE);
}

void printHex(uint64_t num) {
      char buffer[10];
      uintToBase(num, buffer, 16);
      printString(buffer);
}

void printHexWC(uint64_t num, t_colour bgColour, t_colour fontColour) {
      char buffer[10];
      uintToBase(num, buffer, 16);
      printStringWC(buffer, bgColour, fontColour);
}

void printInt(uint64_t num) {
      char buffer[10];
      uintToBase(num, buffer, 10);
      printString("\nrsp: ");
      printString(buffer);
}

void clear(){  
      clearScreen();
}

void deletechar(){ 
      putchar('\b');
}

void staticputchar(char c){
      sys_staticwrite(&c, 1, BLACK, WHITE);
}
