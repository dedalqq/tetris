
all: main.o display.o terminal.o
	gcc -g -o tetris display.o main.o terminal.o

display.o: display.c display.h types.h
	gcc -g -c -o display.o display.c

terminal.o: terminal.c terminal.h types.h
	gcc -g -c -o terminal.o terminal.c

main.o: main.c types.h
	gcc -g -c -o main.o main.c

clean:
	rm terminal.o
	rm display.o
	rm main.o
