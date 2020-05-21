#include <stringLib.h>

static uint8_t * firstMem = (uint8_t *)0xB8000;
static uint8_t * currentVideo = (uint8_t *)0xB8000;

static uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);
static void scrollDown();

/*
La pantalla es un periférico que está mapeado en memoria.En modo texto comienza 0xB8000.
a de 80 columnas y 25 filas, donde cada posición consta de dos componentes
-160 bytes por fila, cada 2 bytes un caracter, cada fila+=0xA0 => cantidad de bytes en pantalla 160*25=4000=FA0
-max dir = B8FA0 - 1 = B8F9F
    -f1=B8000
    -f2=B80A0
    -f3=B8140
    -f4=B81E0
    -f5=B8280
    -f6=B8320
    -f7=B83C0
    -f8=B8460
    -f9=B8500
    -f10=B85A0
    .
    .
    .
*/

void putchar(char c){
    if (currentVideo == (uint8_t *) 0xB8FA0)
    {
        scrollDown();
    }
    *currentVideo++ = c;
    currentVideo++;
}

void deletechar(){
    *currentVideo=' ';
    if (currentVideo > firstMem+1){
        currentVideo-=2;
    }
}

void printString(char * str){
    for (int i = 0; str[i] != 0; i++)
    {
        if(currentVideo == (uint8_t *) 0xB8FA0){
            scrollDown();
        }
        *currentVideo++ = str[i];
        currentVideo++;
    }
}

void printStringWCL(char * str, uint8_t colour, uint64_t count)
{
    for (uint64_t i = 0; i<count && str[i] != 0; i++)
    {
        if (currentVideo == (uint8_t *)0xB8FA0)
        {
            scrollDown();
        }
        *currentVideo++ = str[i];
        *currentVideo= colour != 0 ? colour : *currentVideo;
        currentVideo++;
    }
}

uint8_t strcmp(uint8_t * str1,uint8_t * str2, uint8_t delimiter){
    for (uint8_t i = 0; str1[i] != 0 && str2[i] != 0 && str1[i] != delimiter && str2[i]!=delimiter; i++)
    {
        if(str1[i]!=str2[i])
            return 0;
    }

    return 1;
}


void printStringLn(char *str){
    printString(str);
    newLine();
}

void printInt(uint64_t num){
    char buffer[10];
    uintToBase(num,buffer,10);
    printString(buffer);
}

void printIntLn(uint64_t num){
    char buffer[10];
    uintToBase(num, buffer, 10);
    printString(buffer);
    newLine();
}

void clearScreen(){
    RESET_VID
    while (currentVideo != (uint8_t *)0xB8FA0)
    {
        *currentVideo++ =' ';
        currentVideo++;
    }
    RESET_VID
}

void newLine(){
    do
    {
        putchar(' ');
    } while ((uint64_t)(currentVideo - firstMem) % (WIDTH * 2) != 0);
}

static void scrollDown(){
    memcpy(firstMem, (uint8_t *)(firstMem+WIDTH*2),WIDTH*2*(HEIGHT-1));
    currentVideo = (uint8_t *)(firstMem + WIDTH*2*(HEIGHT-1));
    newLine();
    currentVideo = (uint8_t *)(firstMem + WIDTH*2*(HEIGHT-1));
}



static uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base){
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    //Calculate characters for each digit
    do
    {
        uint32_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    } while (value /= base);

    // Terminate string in buffer.
    *p = 0;

    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return digits;
}
