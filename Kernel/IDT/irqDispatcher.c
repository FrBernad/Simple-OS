#include <timerTick.h>
#include <keyboardDriver.h>
#include <stdint.h>

static void int_20();
static void int_21();

static void (*functions[64])() = {&int_20, &int_21,0};

void irqDispatcher(uint64_t irq)
{
	functions[irq]();
	return;
}

static void int_20() {
	timerHandler();
}

static void int_21(){
	keyboardHandler();
}
