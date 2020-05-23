#include <commands.h>
#include <stringLibrary.h>
#include <clock.h>

//uint8_t **commands = {"help", "inforeg", "printmem", "time", "cpuid", "temp", ""};

void help(){
    printStringLn("These shell commands are defined internally.  Type 'help' to see this list.");
    printStringLn(" >Inforeg: prints the value of all the registers on screen");
    printStringLn(" >Printmem: recieves a pointer and makes a memory dump of 32 bytes on screen");
    printStringLn(" >Time: prints the current system time on screen");
    printStringLn(" >Cpuid: prints the processor brand and model on screen");
    printStringLn(" >Temp: prints the current processor temperature on screen");
}

//todo: print registers, done in assembly
void inforeg() {
   
}

//todo: recieves memory direction and prints 32 bytes after
void printmem(uint8_t * mem) {

}

//todo: desplays system time
void time() {
    uint8_t hours = getDecimalTimeInfo(HOURS);
    uint8_t mins = getDecimalTimeInfo(MINUTES);
    uint8_t secs = getDecimalTimeInfo(SECONDS);
    printString("Time -> ");
    printInt(hours); putChar(':');
    printInt(mins); putChar(':');
    printInt(secs); newLine();
}

//todo: shows processor model and brand
void cpuid() {

}

//todo: shows processor temp
void temp() {

}


