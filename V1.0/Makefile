#Makefile for Falpy Bird Game

CC := gcc
CFLAGS := -c -Wall -I.
LDFLAGS := -lSDL2 -lSDL2_image

programa: main.o SDL_init.o flying_logic.o bird_graphics.o
	${CC} $^ -o programa ${LDFLAGS}

main.o: main.c frontend/SDL_init.h bird.h backend/flying_logic.h frontend/bird_graphics.h 
	${CC} ${CFLAGS} main.c ${LDFLAGS}

SDL_init.o: frontend/SDL_init.c frontend/SDL_init.h screen.h
	${CC} ${CFLAGS} frontend/SDL_init.c ${LDFLAGS}

flying_logic.o: backend/flying_logic.c backend/flying_logic.h frontend/bird_graphics.h bird.h screen.h
	${CC} ${CFLAGS} backend/flying_logic.c ${LDFLAGS}

bird_graphics.o: frontend/bird_graphics.c frontend/bird_graphics.h bird.h screen.h
	${CC} ${CFLAGS} frontend/bird_graphics.c ${LDFLAGS}

clean:
	rm -f *.o backend/*.o frontend/*.o prog

run: programa
	./programa
