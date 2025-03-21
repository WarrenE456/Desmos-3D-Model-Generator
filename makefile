cc = gcc

all: main

main:
	if ! [ -d "build" ]; then mkdir build; fi
	$(cc) src/*.c -o build/main	

clean:
	rm -rf build
