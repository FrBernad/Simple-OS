#include <videoDriver.h>
#include <font.h>
#include <stringLibrary.h>
#include <lib.h>
#include <colours.h>

#define PIXEL_SIZE 3
struct vbe_mode_info_structure
{
    uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;     // deprecated
    uint8_t window_b;     // deprecated
    uint16_t granularity; // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;        // number of bytes per horizontal line
    uint16_t width;        // width in pixels
    uint16_t height;       // height in pixels
    uint8_t w_char;        // unused...
    uint8_t y_char;        // ...
    uint8_t planes;
    uint8_t bpp;   // bits per pixel in this mode
    uint8_t banks; // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direct_color_attributes;

    uint32_t framebuffer; // physical address of the linear frame buffer; write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

static uint32_t * getPixelDataByPosition(uint32_t x, uint32_t y);
static void separateMainScreen();

static struct vbe_mode_info_structure * screen_info = (void *) 0x5C00;
static uint32_t SCREEN_WIDTH = 1024;  //VESA default values
static uint32_t SCREEN_HEIGHT = 768;

static t_screen screens[MAX_SCREENS];
static t_screen * currentScreen;

void initVideoDriver(int BGColour, int FontColour)
{
    t_screen screen1;
    screen1.defaultBGColour = BGColour;
    screen1.defaultFontColour = FontColour;
    screen1.currentX = 0;
    screen1.currentY = 0;
    screen1.offset = CHAR_WIDTH;
    screen1.height = SCREEN_HEIGHT;
    screen1.width = SCREEN_WIDTH / 2 - 2 * CHAR_WIDTH - CHAR_WIDTH;

    screens[0] = screen1;

    t_screen screen2;
    screen2.defaultBGColour = BGColour;
    screen2.defaultFontColour = FontColour;
    screen2.currentX = 0;
    screen2.currentY = 0;
    screen2.offset = SCREEN_WIDTH / 2 + 2 * CHAR_WIDTH;
    screen2.height = SCREEN_HEIGHT;
    screen2.width = SCREEN_WIDTH / 2 - CHAR_WIDTH - 2 * CHAR_WIDTH;

    screens[1] = screen2;

    separateMainScreen();

    currentScreen = &screens[1];

}

void changeScreen(int screen){
    printCharOnScreen(' ', BLACK, WHITE, 0); //for timer tick
    currentScreen = &screens[screen-1];
}

void writePixel(uint32_t x, uint32_t y, int colour)
{
    uint32_t * currentFrame = getPixelDataByPosition(x, y);
    currentFrame[0] = (char)((colour >> 16) & 0xFF); //casteo a char pq sino me tira en azul el 255 255 255 :C
    currentFrame[1] = (char)((colour >> 8) & 0xFF);
    currentFrame[2] = (char)(colour & 0xFF);
}

// 0 x XX XX XX XX
// 0 x 00 FF 00 00 

void printCharOnScreen(char c, int bgColour, int fontColour, int advance)
{

    if (currentScreen->currentX != 0 && currentScreen->width - currentScreen->currentX < CHAR_WIDTH)
    {
        currentScreen->currentY += CHAR_HEIGHT;
        currentScreen->currentX = 0;
        if (currentScreen->currentY == currentScreen->height){
            currentScreen->currentY -= CHAR_HEIGHT;
            scrollDownScreen();
        }
    }

    // if (SCREEN_WIDTH - currentScreen->currentX < CHAR_WIDTH || SCREEN_HEIGHT - currentScreen->currentY < CHAR_HEIGHT){
    //     return;
    // }

    char * charMap = getCharMap(c);

    uint32_t x = currentScreen->currentX + currentScreen->offset, y = currentScreen->currentY;
    
    for (int i = 0; i < CHAR_HEIGHT; i++)
    {
        for (int j = 0; j < CHAR_WIDTH; j++)
        {
            int8_t isFont = (charMap[i] >> (CHAR_WIDTH - j - 1)) & 0x01;
            if (isFont)
            {
                writePixel(x, y, currentScreen->defaultFontColour);
            }
            else
            {
                writePixel(x, y, currentScreen->defaultBGColour);
            }
            x++;
        }
        x = currentScreen->currentX + currentScreen->offset;
        y++;
    }
    
    if (advance)
    {
        currentScreen->currentX += CHAR_WIDTH;
    }
    
}

void scrollDownScreen(){
    memcpy((void *)((uint64_t)screen_info->framebuffer),
           (void *)((uint64_t)screen_info->framebuffer + SCREEN_WIDTH * CHAR_HEIGHT* PIXEL_SIZE), 
            PIXEL_SIZE * SCREEN_WIDTH * (SCREEN_HEIGHT-CHAR_HEIGHT));
    clearLineOnScreen();
}

void clearLineOnScreen(){
    for (int i = 0; i < CHAR_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            writePixel(j, currentScreen->currentY + i, currentScreen->defaultBGColour);
        }
    }
}

void removeCharFromScreen(){
    if (currentScreen->currentX == 0)
    {
        if(currentScreen->currentY == 0){
            return;
        }
        currentScreen->currentY -= CHAR_HEIGHT;
        currentScreen->currentX = currentScreen->width;
    }

    currentScreen->currentX -= CHAR_WIDTH;

    uint32_t x = currentScreen->currentX + currentScreen->offset, y = currentScreen->currentY;

    for (int i = 0; i < CHAR_HEIGHT; i++)
    {
        for (int j = 0; j < CHAR_WIDTH; j++)
        {
            writePixel(x, y, currentScreen->defaultBGColour);
            x++;
        }
        x = currentScreen->currentX + currentScreen->offset;
        y++;
    }
}

void changeLineOnScreen(){
    printCharOnScreen(' ', BLACK, WHITE, 0); //for timer tick
    currentScreen->currentY+=CHAR_HEIGHT;
    currentScreen->currentX=0;
    if (currentScreen->currentY == currentScreen->height)
    {
        currentScreen->currentY -= CHAR_HEIGHT;
        scrollDownScreen();
    }
}

void clearScreen(){
    for (int y = 0; y < currentScreen->height; y++)
    {
        for (int x = 0; x < currentScreen->width; x++)
        {
            writePixel(x + currentScreen->offset, y, currentScreen->defaultBGColour);
        }
    }
    currentScreen->currentX = 0;
    currentScreen->currentY = 0;
}

static uint32_t * getPixelDataByPosition(uint32_t x, uint32_t y)
{
   return (uint32_t*)((uint64_t)screen_info->framebuffer + PIXEL_SIZE * (x + y * SCREEN_WIDTH)); //prque casteo a 64 funciona?
}

static void separateMainScreen(){
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < 2*CHAR_WIDTH; x++)
        {
            writePixel(SCREEN_WIDTH/2-CHAR_WIDTH+x,y,WHITE);
        }
    }
}

//00110010
//each letter ocuppies 8*16=48pix my total is 1024*768=786.432 => total chars=16.384
//in every row max chars = 1024/8=128
