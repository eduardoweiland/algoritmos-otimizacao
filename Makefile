.PHONY: all max_flow tsp clean

all: max_flow tsp

max_flow:
	@(cd max_flow && make all)

tsp:
	@(cd tsp && make all)

clean:
	@(cd max_flow && make clean)
	@(cd tsp && make clean)

