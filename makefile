CC = gcc
FILES = src/day1.c
OUT_EXE = main

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core

rebuild: clean build
