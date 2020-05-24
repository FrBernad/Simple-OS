include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin

SOURCES= $(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_UTILS=$(wildcard utils/*.c)
SOURCES_APPLICATIONS=$(wildcard applications/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_UTILS=$(SOURCES_UTILS:.c=.o)
OBJECTS_APPLICATIONS=$(SOURCES_APPLICATIONS:.c=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_UTILS) $(OBJECTS_APPLICATIONS)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $^

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o applications/*.o asm/*.o *.bin utils/*.o

.PHONY: all clean print
