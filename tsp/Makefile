CFLAGS  = -Wall -Wextra -Werror
LIBS    = -lm
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

.PHONY: all clean

all: tsp

clean:
	rm $(OBJECTS) tsp

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

tsp: $(OBJECTS)
	gcc -o $@ $(OBJECTS) $(CFLAGS) $(LIBS)

