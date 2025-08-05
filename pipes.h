#ifndef PIPES_H
#define PIPES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#define GAP_PWP 200 //Gap beween pipes
#define MAX_PIPES_WIDTH 150 //Max width a dynamic pipe can have
#define MIN_PIPES_WIDTH 80 //Min width a dynamic pipe can have
#define PIPES_WIDTH 100 //Width of the pipes
#define PIPES_GAP 250 //size of gap
#define NUM_PIPES 5 //number of pipes

typedef struct{
    SDL_Texture* up_pipe_texture; //pipe texture
    SDL_Texture* down_pipe_texture; //pipe texture
    int width; //Width of the pipe
    int position; //X position for the pipe
    int gap_height;  //height of gap
    int speed; //Speed of the pipe
    bool bounce_width; //Flag to know whether the pipe is bouncing or not
    bool d_pipe; //Flag to know whether the pipe is dynamic or not
    bool bounced; //Flag to know whether the pipe has bounced
    bool has_passed;//Flag to know whhether the bird has passed the pipe 
}pipe_t;

void pipes_movement(SDL_Renderer** renderer,pipe_t *pipe, int difficulty);
//Function that initialize the position and the gap height
void init_pipes (pipe_t * pipe, int pos, int difficulty, bool update);
//Function that draws tthe pipes
void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe);
#endif// PIPES_H