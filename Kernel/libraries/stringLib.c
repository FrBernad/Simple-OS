#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

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
      printString(buffer);
}

void clear(){  
      sys_clear();
}

void deletechar(){ 
      putchar('\b');
}

void staticputchar(char c){
      sys_staticwrite(&c, 1, BLACK, WHITE);
}
