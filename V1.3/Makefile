#Makefile for Falpy Bird Game

CC := gcc
CFLAGS := -c -Wall -I.
LDFLAGS := -lSDL2 -lSDL2_image

Flappy_Bird: main.o bird.o pipes.o screen.o
	${CC} $^ -o Flappy_Bird ${LDFLAGS}

main.o: main.c bird.h pipes.h screen.h
	${CC} ${CFLAGS} main.c 

bird.o: bird.c bird.h screen.h
	${CC} ${CFLAGS} bird.c 

pipes.o: pipes.c pipes.h screen.h
	${CC} ${CFLAGS} pipes.c 

screen.o: screen.c screen.h 
	${CC} ${CFLAGS} screen.c 

clean:
	rm -f *.o backend/*.o frontend/*.o prog

run: Flappy_Bird
	./Flappy_Bird
