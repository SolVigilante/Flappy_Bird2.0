#Makefile for Falpy Bird Game

CC := gcc
CFLAGS := -c -Wall -I.
LDFLAGS := -lSDL2 -lSDL2_image

programa: main.o SDL_init.o flying_logic.o bird_graphics.o pipes_logic.o pipes_graphics.o
	${CC} $^ -o programa ${LDFLAGS}

main.o: main.c frontend/SDL_init.h bird.h backend/flying_logic.h frontend/bird_graphics.h frontend/pipes_graphics.h backend/pipes_logic.h screen.h
	${CC} ${CFLAGS} main.c 

SDL_init.o: frontend/SDL_init.c frontend/SDL_init.h screen.h
	${CC} ${CFLAGS} frontend/SDL_init.c 

flying_logic.o: backend/flying_logic.c backend/flying_logic.h frontend/bird_graphics.h bird.h screen.h
	${CC} ${CFLAGS} backend/flying_logic.c 

bird_graphics.o: frontend/bird_graphics.c frontend/bird_graphics.h bird.h screen.h
	${CC} ${CFLAGS} frontend/bird_graphics.c 

pipes_logic.o: backend/pipes_logic.c backend/pipes_logic.h pipes.h frontend/pipes_graphics.h screen.h
	${CC} ${CFLAGS} backend/pipes_logic.c

pipes_graphics.o: frontend/pipes_graphics.c frontend/pipes_graphics.h pipes.h screen.h
	${CC} ${CFLAGS} frontend/pipes_graphics.c

clean:
	rm -f *.o backend/*.o frontend/*.o prog

run: programa
	./programa
