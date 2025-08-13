#ifndef CONSTANTS_H
#define CONSTANTS_H

//Player constants
#define START_DIFFICULTY -1
#define HEART_HEIGHT 50
#define HEART_WIDTH 150
#define MAX_USERNAME_LENGTH 20
#define GAMEOVER 0
#define CHOOSING_DIFFICULTY 1
#define CHOOSING_USERNAME 2
#define FIRST_KEY 3
#define PLAYING 4
#define CLOSING_GAME 5
//logic constants
#define EASY 'E'
#define MEDIUM 'M'
#define HARD 'H'
//pipes constants
#define GAP_PWP 200 //Gap beween pipes
#define MAX_PIPES_WIDTH 150 //Max width a dynamic pipe can have
#define MIN_PIPES_WIDTH 80 //Min width a dynamic pipe can have
#define PIPES_WIDTH 100 //Width of the pipes
#define PIPES_GAP 250 //size of gap
#define NUM_PIPES 5 //number of pipes
//bird constants
#define GRAVITY 100.0f //Gavity constant
#define BIRD_WIDTH 50
#define BIRD_HEIGHT 50
#define FLYING_BIRD ' ' //Constant that indicates the bird is flying
#define FALLING_BIRD '0' //constant that indicates the bird is falling
//Screen constants
#define SCREEN_WIDTH 1000 //Width of the screen
#define SCREEN_HEIGHT 800 //Height of the screen

#endif // CONSTANTS_H