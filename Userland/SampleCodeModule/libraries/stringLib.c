#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

void printString(char* str) {
      sys_write(str, strlen(str), BLACK, WHITE);
}

void printStringWC(char* str, t_colour bgColour, t_colour fontColour) {
      sys_write(str, strlen(str), bgColour, fontColour);
}

void printStringLn(char* str) {
      printString(str);
      putchar('\n');
}

char getchar(){
      return sys_getchar();
}

void putchar(char c) {
      sys_write(&c, 1, BLACK, WHITE);
}

void putcharWC(char c, t_colour bgColour, t_colour fontColour) {
      sys_write(&c, 1, bgColour, fontColour);
}

void printHex(uint64_t num) {
      char buffer[10];
      uintToBase(num, buffer, 16);
      printString(buffer);
}

void printInt(uint64_t num) {
      char buffer[10];
      uintToBase(num, buffer, 10);
      printString(buffer);
}

// void printDouble(double num){
//       char buffer[10];
//       ftoa(num,buffer,4);
//       printString(buffer);
// }

void clear() {
      sys_clear();
}

void deletechar() {
      putchar('\b');
}

void staticputchar(char c) {
      sys_staticwrite(&c, 1, BLACK, WHITE);
}

void strcpy(char* str1, char* str2){  //copies str1 into str2
      int i;
      for (i = 0; str1[i] != 0; i++) {
            str2[i]=str1[i];
      }
      str2[i]=0;
}
