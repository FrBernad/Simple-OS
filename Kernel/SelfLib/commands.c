#include <commands.h>
#include <stringLibrary.h>

//uint8_t **commands = {"help", "inforeg", "printmem", "time", "cpuid", "temp", ""};
static int bcd_to_decimal(uint8_t x);
uint8_t getRTCsecs();
uint8_t getRTChours();
uint8_t getRTCmins();

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
    int hours = bcd_to_decimal(getRTChours());
    int mins = bcd_to_decimal(getRTCmins());
    int secs = bcd_to_decimal(getRTCsecs());
    printString("Time -> ");
    printInt((uint64_t)hours); putChar(':');
    printInt((uint64_t)mins); putChar(':');
    printInt((uint64_t)secs); newLine();
}

//todo: shows processor model and brand
void cpuid() {

}

//todo: shows processor temp
void temp() {

}

//Funcion que pasa de BinaryCodedDecimal a decimal 
//Sacada de StackOverFLow: -> https://stackoverflow.com/a/42340213
static int bcd_to_decimal(uint8_t x) {
    return x - 6 * (x >> 4);
}

