SRCS = gpioLib.c main.c
PROG := gpioLib_test
CFLAGS = -O0 -g -Wall

MACHINE=colibri-t20

OECORE_NATIVE_SYSROOT ?= $(HOME)/oe-core/build/out-eglibc/sysroots/i686-linux/
OECORE_TARGET_SYSROOT ?= $(HOME)/oe-core/build/out-eglibc/sysroots/$(MACHINE)/
CROSS_COMPILE ?= $(OECORE_NATIVE_SYSROOT)usr/bin/armv7ahf-vfp-angstrom-linux-gnueabi/arm-angstrom-linux-gnueabi-

# Toolchain binaries
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
STRIP = $(CROSS_COMPILE)strip
RM = rm -f

# Sets the output filename and object files
PROG := $(PROG)$(BIN_POSTFIX)
OBJS = $(SRCS:.c=$(BIN_POSTFIX).o)
DEPS = $(OBJS:.o=.o.d)

# pull in dependency info for *existing* .o files
-include $(DEPS)

all: $(PROG)

$(PROG): $(OBJS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)
	#$(STRIP) $@ 

%$(BIN_POSTFIX).o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
	$(CC) -MM $(CFLAGS) $< > $@.d

clean:
	$(RM) $(OBJS) $(PROG) $(DEPS) *.o *.o.d *.x86

.PHONY: all clean
