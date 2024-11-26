CC=C:\avr\bin\avr-g++
LD=C:\avr\bin\avr-ld
OBJCOPY="C:\avr\bin\avr-objcopy"
OBJDUMP="C:\avr\bin\avr-objdump"
AVRSIZE="C:\avr\bin\avr-size"
OBJISP="C:\avr\bin\avrdude"
MCU=atmega328p
CFLAGS=-Wall -Wextra  -Wundef -pedantic \
		-Os -std=gnu99 -DF_CPU=16000000UL -mmcu=${MCU} -DBAUD=19200
LDFLAGS=-mmcu=$(MCU)
PORT=\\\\.\\COM3
BIN=avrdemo
OUT=${BIN}.hex
SOURCES = main.cpp

DEBUG?=1

ifeq ($(DEBUG), 1)
	OUTPUTDIR=bin/debug
else
	OUTPUTDIR=bin/release
endif

OBJS =  $(addprefix $(OUTPUTDIR)/,$(SOURCES:.cpp=.o))

all: $(OUTPUTDIR)  $(OUT) 

$(OBJS): Makefile

$(OUTPUTDIR)/%.o:%.cpp
	$(CC) $(CFLAGS) -MD -o $@ -c $<

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@


$(OBJS):$(SOURCES)

%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

isp: ${BIN}.hex
	$(OBJISP) -F -V -c arduino -p ${MCU} -P ${PORT} -U flash:w:$<


clean:
	del "$(OUT)"  *.map *.P *.d

$(OUTPUTDIR): 
	@mkdir "$(OUTPUTDIR)"
		   	
.PHONY: clean dirs
