cc = gcc

all: main

main:
	if ! [ -d "build" ]; then mkdir build; fi
	$(cc) src/*.c -o build/dtmg	

clean:
	rm -rf build
