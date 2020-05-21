#include <keyboard.h>
#include <keyboardInfo.h>
#include <commands.h>
#include <keys.h>

#define BUFFER_SIZE 50

static uint8_t action(uint8_t scanCode);
static void checkCommand();

static const char pressCodes[KEYS][2] =
    {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'},
    {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('},
    {'0', ')'}, {'-', '_'}, {'=', '+'}, {0, 0}, {0, 0}, {'q', 'Q'}, 
    {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, 
    {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, 
    {']', '}'}, {0, 0}, {0, 0}, {'a', 'A'}, {'s', 'S'}, 
    {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'},
    {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'},
    {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, 
    {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, 
    {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

static uint8_t scanCode, currentAction, specialChars = 0, capsLock = 0, bufferIndx = 0;
static uint8_t buffer[BUFFER_SIZE]={0};
static t_command commands[] = {{&help, "help"}, {&inforeg, "inforeg"}, {&printmem, "printmem"}, {&time, "time"}, {&cpuid, "cpuid"}, {&temp, "temp"}, {0 , ""}};

void
keyboard_handler()
{
    if (hasKey())
    {
        scanCode = getKey();
        currentAction = action(scanCode);
        printString("buffer:");
        printStringLn(buffer);
        if (currentAction == PRESSED)
        {
            switch (scanCode)
            {
            case L_SHFT:
            case R_SHFT:
                specialChars = 1;
                break;

            case ENTER:
                checkCommand();
                newLine();
                break;

            case CAPS_LCK:
                capsLock = capsLock == 1 ? 0 : 1;
                break;

            case SPACE:
                putchar(' ');
                break;

            case B_SPACE:
                deletechar();
                break;

            default:
                if (pressCodes[scanCode][0])
                {
                    uint8_t letter;
                    if (!IS_LETTER(pressCodes[scanCode][0])){
                        letter = pressCodes[scanCode][specialChars];
                        buffer[bufferIndx++]= letter;
                        putchar(letter);
                    }
                    else{
                        letter = pressCodes[scanCode][ABS(capsLock - (specialChars))];
                        buffer[bufferIndx++] = letter;
                        putchar(letter);
                    }
                }
            }
        }
        else if (currentAction == RELEASED)
        {
            switch (scanCode)
            {
            case L_SHFT | 0x80:
            case R_SHFT | 0x80:
                specialChars = 0;
                break;
            }
        }
    }
}

static void checkCommand(){
    uint32_t command,found=0;

    for (command = 0; commands[command].command != 0 && !found; command++)
    {
        if(strcmp(commands[command].name,buffer,' ')==0)
            found=1;
    }

    if(found){
        switch(command){
            case HELP:
                commands[HELP].command();
                break;
            case INFOREG:
                commands[INFOREG].command();
                break;
            case PRINTMEM:
                commands[PRINTMEM].command();
                break;
            case TIME:
                commands[TIME].command();
                break;
            case CPUID:
                commands[CPUID].command();
                break;
            case TEMP:
                commands[TEMP].command();
                break;
        }
    }

    else{
        printStringLn("Invalid command");
    }
    
}

static uint8_t action(uint8_t scanCode)
{
    if (scanCode >= 0x01 && scanCode <= 0x3A)
        return PRESSED;
    else if (scanCode >= 0x81 && scanCode <= 0xBA)
        return RELEASED;

    return ERRROR;
}
