#Makefile for Falpy Bird Game

CC := gcc
CFLAGS := -c -Wall -I.
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf

Flappy_Bird: main.o bird.o pipes.o screen.o logic.o player.o
	${CC} $^ -o Flappy_Bird ${LDFLAGS}

main.o: main.c bird.h pipes.h screen.h logic.h player.h
	${CC} ${CFLAGS} main.c 

bird.o: bird.c bird.h screen.h
	${CC} ${CFLAGS} bird.c 

pipes.o: pipes.c pipes.h screen.h
	${CC} ${CFLAGS} pipes.c 

screen.o: screen.c screen.h 
	${CC} ${CFLAGS} screen.c 

logic.o: logic.c logic.h bird.h pipes.h screen.h player.h
	${CC} ${CFLAGS} logic.c 

player.o: player.c player.h
	${CC} ${CFLAGS} player.c

clean:
	rm -f *.o 

run: Flappy_Bird
	./Flappy_Bird
