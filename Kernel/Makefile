include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_EXCEPCIONES=$(wildcard IDT/*.c)
SOURCES_EXCEPCIONES_ASM=$(wildcard IDT/*.asm)
SOURCES_SELF_LIB_ASM=$(wildcard SelfLib/*.asm)
SOURCES_SELF_LIB=$(wildcard SelfLib/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_EXCEPCIONES=$(SOURCES_EXCEPCIONES:.c=.o)
OBJECTS_EXCEPCIONES_ASM=$(SOURCES_EXCEPCIONES_ASM:.asm=.o)
OBJECTS_SELF_LIB=$(SOURCES_SELF_LIB:.c=.o)
OBJECTS_SELF_LIB_ASM=$(SOURCES_SELF_LIB_ASM:.asm=.o)

LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_EXCEPCIONES) $(OBJECTS_EXCEPCIONES_ASM) $(OBJECTS_SELF_LIB) $(OBJECTS_SELF_LIB_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $@ $^

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -I./IDT -I./SelfLib -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin IDT/*.o SelfLib/*.o

.PHONY: all clean
