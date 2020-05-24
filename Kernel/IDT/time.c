#include <time.h>
#include <videoDriver.h>
#include <colours.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	// if (ticks_elapsed() % 7 == 0)
	// {
	// 	printCharOnScreen('|',BLACK,WHITE,0);
	// }
	// if (ticks_elapsed() % 13 == 0)
	// {
	// 	printCharOnScreen(' ', BLACK, WHITE, 0);
	// }
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
