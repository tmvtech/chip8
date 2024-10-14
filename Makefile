OUT_DIR=.
OUT_NAME=chip8

ELF=$(OUT_DIR)/$(OUT_NAME).elf
DIS=$(OUT_DIR)/$(OUT_NAME).dasm

#=====================================================================
# Compiler
CC=g++
#=====================================================================
# Project Paths

#=====================================================================
# Files to compile
ASMFILES=


CFILES=



CPPFILES= 	main.cpp				\
			logger.cpp				\
			cmdLineParser.cpp		\
			chip8.cpp				\
			romLoader.cpp			\
			cpu.cpp					\
			displaysdl.cpp			\
			keyboardsdl.cpp			\
			soundsdl.cpp			\

			


# Create obj files names from source files
ASMOBJS=$(patsubst %.S,%.o,$(ASMFILES))
COBJS=$(patsubst %.c,%.o,$(CFILES))
CPPOBJS=$(patsubst %.cpp,%.o,$(CPPFILES))

OBJS=$(ASMOBJS) $(COBJS) $(CPPOBJS)
# ==================================================================
# Header flags
CC_HEADERS= -I/usr/include/SDL2


# Compiler flags
CC_FLAGS= -g -std=c++20 -lSDL2


# Linker flags
LD_FLAGS=


#===================================================================
# all rule
all: directory $(ELF)

#===================================================================
#generate .elf file
$(ELF): $(OBJS)
	$(CC) $(LD_FLAGS) -o $@ $(OBJS) $(CC_HEADERS) $(CC_FLAGS)

%.o: %.S
	$(CC) $(CC_FLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CC_FLAGS) -c -o $@ $<

%.o: %.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

directory:
	mkdir -p $(OUT_DIR)

.PHONY: clean
clean:
	rm -f $(OBJS) $(ELF)

#=====================================================================
# Debug section
print:
	$(info    OBJS is $(OBJS))
	$(info    CPPOBJS is $(CPPOBJS))
	$(info    CC is $(CC))

