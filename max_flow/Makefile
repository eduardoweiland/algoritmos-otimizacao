CFLAGS  = -Wall -Wextra -Werror
LIBS    =
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

.PHONY: all clean

all: max_flow

clean:
	rm $(OBJECTS) max_flow

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

max_flow: $(OBJECTS)
	gcc -o $@ $(OBJECTS) $(CFLAGS) $(LIBS)

