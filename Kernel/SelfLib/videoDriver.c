#include <videoDriver.h>
#include <font.h>
#include <stringLibrary.h>
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

static struct vbe_mode_info_structure * screen_info = (void *) 0x5C00;

static uint32_t WIDTH = 1024;  //VESA default values
static uint32_t HEIGHT = 768;

static uint32_t currentX = 0;
static uint32_t currentY = 0;

static uint32_t * getPixelDataByPosition(uint32_t x, uint32_t y)
{
    return (uint32_t*)((uint32_t)screen_info->framebuffer + 3 * (x + y * WIDTH));
}

void writePixel(uint32_t x, uint32_t y, char colour[RGB])
{
    uint32_t * currentFrame = getPixelDataByPosition(x, y);
    currentFrame[0] = colour[0];
    currentFrame[1] = colour[1];
    currentFrame[2] = colour[2];
}

void printCharOnScreen(char c, char bgColour[RGB], char fontColour[RGB])
{
    if (currentX != 0 && currentX == WIDTH)
    {
        currentY += CHAR_HEIGHT;
        currentX = 0;
    }

    if (WIDTH - currentX < CHAR_WIDTH || HEIGHT - currentY < CHAR_HEIGHT){
        return;
    }

    char * charMap = getCharMap(c);


    uint32_t x = currentX, y = currentY;

    
    for (int i = 0; i < CHAR_HEIGHT; i++)
    {
        for (int j = 0; j < CHAR_WIDTH; j++)
        {
            int8_t isFont = (charMap[i] >> (CHAR_WIDTH - j - 1)) & 0x01;
            if (isFont)
            {
                writePixel(x, y, fontColour);
            }
            else
            {
                writePixel(x, y, bgColour);
            }
            x++;
        }
        x = currentX;
        y++;
    }
    currentX += CHAR_WIDTH;
}

void removeCharFromScreen(char bgColour[RGB])
{
    if(currentX%WIDTH<CHAR_WIDTH){
        return;
    }

    currentX-=CHAR_WIDTH;

    uint32_t x = currentX, y = currentY;

    for (int i = 0; i < CHAR_HEIGHT; i++)
    {
        for (int j = 0; j < CHAR_WIDTH; j++)
        {
            writePixel(x, y, bgColour);
            x++;
        }
        x = currentX;
        y++;
    }
}

void changeLineOnScreen(){
    currentY+=CHAR_HEIGHT;
    currentX=0;
}

void clearScreen(char bgColour[RGB]){
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            writePixel(i, j, bgColour);
        }
    }
    currentX = 0;
    currentY = 0;
}
//00110010
//each letter ocuppies 8*16=48pix my total is 1024*768=786.432 => total chars=16.384
//in every row max chars = 1024/8=128
