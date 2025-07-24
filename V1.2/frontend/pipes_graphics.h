#ifndef PIPES_GRAPHICS_H
#define PIPES_GRAPHICS_H
#include "../pipes.h"
#include <SDL2/SDL.h>
//Function that initialize the position and the gap height
void init_pipes (pipe_t * pipe, int pos);
//Function that draws tthe pipes
void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe);
#endif //PIPES_GRAPHICS_H