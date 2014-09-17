CC=gcc
CCFLAGS=-std=c89 -Wall -O3 -I.
LD=gcc
LDFLAGS=-L.

TARGET=wake_on_lan
SRCS=mac_addr.c net.c wake_on_lan.c
HDRS=mac_addr.h wake_on_lan.h
OBJS=$(addsuffix .o,$(basename $(SRCS)))

all: $(TARGET)

$(OBJS): $(HDRS)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ && strip $(TARGET)

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f *.o

.PHONY: distclean
distclean:
	make clean && rm -f $(TARGET)

