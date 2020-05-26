#include <stringLib.h>
#include <systemCalls.h>
#include <utils.h>

char getchar(){
      return sys_getchar();
}

void printString(char * str) {
      sys_write(str,strlen(str));
}

void printStringLn(char* str) {
      printString(str);
      newLine();
}

void putchar(char c){
      sys_write(&c,1);
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

void clear(){  
      sys_clear();
}

void newLine(){
      sys_newLine();
}
void deletechar(){ 
      sys_deletechar();
}

void staticputchar(char c){
      sys_staticwrite(&c,1);
}

int strlen(char * str){
      int size = 0;
      for (int i = 0; str[i] != 0; i++) {
            size++;
      }
      return size;
}
