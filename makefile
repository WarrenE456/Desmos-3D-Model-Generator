cc = gcc

all: main

main:
	if ! [ -d "build" ]; then mkdir build; fi
	$(cc) src/main.c -o build/main	

clean:
	rm -rf build
