#include <commands.h>
#include <stringLibrary.h>

//uint8_t **commands = {"help", "inforeg", "printmem", "time", "cpuid", "temp", ""};

void help(){
    printStringLn("Help: prints all available commands");
    printStringLn("Inforeg: prints the value of all the registers on screen");
    printStringLn("Printmem: recieves a pointer and makes a memory dump of 32 bytes on screen");
    printStringLn("Time: prints the current system time on screen");
    printStringLn("Cpuid: prints the processor brand and model on screen");
    printStringLn("Temp: prints the current processor temperature on screen");

}

//todo: print registers, done in assembly
void inforeg() {
   
}

//todo: recieves memory direction and prints 32 bytes after
void printmem(uint8_t * mem) {

}

//todo: desplays system time
void time() {
    
}

//todo: shows processor model and brand
void cpuid() {

}

//todo: shows processor temp
void temp() {

}


