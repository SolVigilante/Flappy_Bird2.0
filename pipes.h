#ifndef PIPES_H
#define PIPES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#define GAP_PWP 200 //Gap beween pipes
#define PIPES_WIDTH 100 //the pipes always have the same width
#define PIPES_GAP 250 //size of gap
#define NUM_PIPES 5 //number of pipes

typedef struct{
    SDL_Texture* up_pipe_texture; //pipe texture
    SDL_Texture* down_pipe_texture; //pipe texture
    int position; //X position for the pipe
    int gap_height;  //height of gap
    int speed; //Speed of the pipe
    bool d_pipe; //Flag to know whether the pipe is dynamic or not
    bool bounced; //Flag to know whether the pipe has bounced
    bool collided; //Flag to know whether the bird has collided
    bool has_passed;//Flag to know whhether the bird has passed the pipe 
}pipe_t;

void pipes_movement(SDL_Renderer** renderer,pipe_t *pipe, int difficulty);
//Function that initialize the position and the gap height
void init_pipes (pipe_t * pipe, int pos, int difficulty, bool update);
//Function that draws tthe pipes
void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe);
#endif// PIPES_H