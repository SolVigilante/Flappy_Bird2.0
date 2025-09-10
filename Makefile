#Makefile for Falpy Bird Game

CC := gcc
CFLAGS := -c -g -Wall -I.
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lm

Flappy_Bird: main.o bird.o pipes.o pipes_front.o screen.o logic.o player.o player_front.o history_log.o history_log_front.o bird_front.o pipes_front.o time.o
	${CC} $^ -o Flappy_Bird ${LDFLAGS}

main.o: main.c Backend/bird.h Frontend/bird_front.h Backend/pipes.h Frontend/pipes_front.h Frontend/screen.h Backend/logic.h Backend/player.h Frontend/player_front.h Backend/constants.h Frontend/history_log_front.h Backend/history_log.h Backend/time.h
	${CC} ${CFLAGS} main.c 

bird.o: Backend/bird.c Backend/bird.h Frontend/screen.h Backend/constants.h
	${CC} ${CFLAGS} Backend/bird.c 

bird_front.o: Frontend/bird_front.c Frontend/bird_front.h Backend/time.h
	${CC} ${CFLAGS} Frontend/bird_front.c

pipes.o: Backend/pipes.c Backend/pipes.h Backend/constants.h Frontend/pipes_front.h 
	${CC} ${CFLAGS} Backend/pipes.c 

pipes_front.o : Frontend/pipes_front.c Frontend/pipes_front.h Backend/constants.h
	${CC} ${CFLAGS} Frontend/pipes_front.c

screen.o: Frontend/screen.c Frontend/screen.h Backend/constants.h
	${CC} ${CFLAGS} Frontend/screen.c 

logic.o: Backend/logic.c Backend/logic.h Backend/bird.h Backend/pipes.h Frontend/screen.h Backend/constants.h
	${CC} ${CFLAGS} Backend/logic.c 

player.o: Backend/player.c Backend/player.h Backend/constants.h 
	${CC} ${CFLAGS} Backend/player.c

player_front.o: Frontend/player_front.c Frontend/player_front.h Backend/constants.h Frontend/screen.h
	${CC} ${CFLAGS} Frontend/player_front.c

history_log.o: Backend/history_log.c Backend/history_log.h Backend/constants.h Frontend/screen.h
	${CC} ${CFLAGS} Backend/history_log.c

history_log_front.o: Frontend/history_log_front.c Frontend/history_log_front.h Backend/constants.h
	${CC} ${CFLAGS} Frontend/history_log_front.c

time.o : Backend/time.c Backend/time.h
	${CC} ${CFLAGS} Backend/time.c

clean:
	rm -f *.o 

run: Flappy_Bird
	./Flappy_Bird