$(CC)=gcc

all: main

debug:
	./main < input.txt 

main: main.o
	$(CC) main.o -o main

main.o:
	$(CC) -c main.c	

clean:
	$(RM) -rf *.o main
