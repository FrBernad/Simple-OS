#include <time.h>
#include <stringLib.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	/*if(ticks%(18*5)==0)
	{
		printString("Han pasado: ");
		printInt(ticks/18);
		printStringLn(" segundos");
	}*/
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
