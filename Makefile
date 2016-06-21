SRCS=$(wildcard *.c)
BINS=$(basename $(SRCS))
CC=gcc
CFLAGS=-std=c99

all:	$(BINS)

.PHONY:	clean

clean:
	rm -f $(BINS)
