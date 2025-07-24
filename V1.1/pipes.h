#ifndef PIPES_H
#define PIPES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define PIPES_WIDTH 100 //the pipes always have the same width
#define PIPES_GAP 150 //size of gap

typedef struct{
    SDL_Texture* up_pipe_texture; //pipe texture
    SDL_Texture* down_pipe_texture; //pipe texture
    int position; //X position for the pipe
    int gap_height;  //height of gap
}pipe_t;
#endif// PIPES_H