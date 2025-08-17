#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
//Player 
//Constants
#define MAX_SCORE 100
#define START_DIFFICULTY -1
#define HEART_HEIGHT 50
#define HEART_WIDTH 150
#define MAX_USERNAME_LENGTH 20
#define GAMEOVER 0
#define CHOOSING_DIFFICULTY 1
#define CHOOSING_SLOT 6
#define CHOOSING_USERNAME 2
#define FIRST_KEY 3
#define PLAYING 4
#define RENAME 5
#define DO_REWRITE 4
#define NO_REWRITE 5
#define START_SLOT 7


//Struct
typedef struct{
    char * slot;
    int rewrite;
}slot_info_t;
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int status; 
    int lives;
    slot_info_t slot_info;
    SDL_Texture* username_texture;
    SDL_Texture * lives_texture;
    TTF_Font* score_font;
    TTF_Font* username_font;
    SDL_Texture* enter_username_texture;
    SDL_Texture* score_text_texture;
    int score;
}player_t;

//logic constants
#define EASY 'E'
#define MEDIUM 'M'
#define HARD 'H'
#define SPEED_LIMIT(difficulty) (((difficulty) == HARD) ? 15 : ((difficulty) == MEDIUM) ? 7 : 4) //Speed limit for each difficulty

//pipes 
// constants
#define GAP_PWP 200 //Gap beween pipes
#define MAX_PIPES_WIDTH 150 //Max width a dynamic pipe can have
#define MIN_PIPES_WIDTH 80 //Min width a dynamic pipe can have
#define PIPES_WIDTH 100 //Width of the pipes
#define PIPES_GAP 250 //size of gap
#define NUM_PIPES 5 //number of pipes
//Struct
typedef struct{
    SDL_Texture* up_pipe_texture; //pipe texture
    SDL_Texture* down_pipe_texture; //pipe texture
    long long last_increment_time; //Last time the speed was increased
    int width; //Width of the pipe
    int position; //X position for the pipe
    int gap_height;  //height of gap
    int speed; //Speed of the pipe
    bool bounce_width; //Flag to know whether the pipe is bouncing or not
    bool d_pipe; //Flag to know whether the pipe is dynamic or not
    bool bounced; //Flag to know whether the pipe has bounced
    bool has_passed;//Flag to know whhether the bird has passed the pipe 
}pipe_t;

//bird constants
#define GRAVITY 100.0f //Gavity constant
#define BIRD_WIDTH 50
#define BIRD_HEIGHT 50
#define FLYING_BIRD ' ' //Constant that indicates the bird is flying
#define FALLING_BIRD '0' //constant that indicates the bird is falling
//Struct
typedef struct{
    SDL_Texture* bird_texture; //Image for the bird texture
    int bird_height; 
    int bird_width;
    long long last_collision_time; //Last time the bird collided, initialized to a negative value so the first increment cant happen immediately
    long long last_gravity_time; //Last time the gravity was applied
    bool space_pressed; //Space flag, for key control
    bool floor_collision; //Flag to know whether the bird has collided with the floor
    bool collided; //Flag to know whether the bird has collided
    int bird_x; //X position of the bird
    int bird_y; //Y position of the bird
    float velocity; //Velocitty of the bird
    float acceleration; //Acceleration of the bird
}bird_t;

//Screen
// constants
#define SCREEN_WIDTH 1000 //Width of the screen
#define SCREEN_HEIGHT 800 //Height of the screen
//Struct
typedef struct{
    SDL_Texture* start_texture; //Texture for the start screen
    SDL_Texture* gameover_texture; //Texture for the game over screen
    SDL_Texture* speed_up_texture; //Texture for the speed up screen
    SDL_Texture* choose_difficulty_texture; //Texture for the choose difficulty screen
    SDL_Texture* choose_slot_texture; //Texture for the choose difficulty screen
    SDL_Texture * choose_rename_texture;
}letter_texture_t;

#endif // CONSTANTS_H