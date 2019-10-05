all: main.c
	cc -I includes/ main.c src/*.c -o main.out
clean: main.out
	rm -f main.out