#ifndef PIPES_H
#define PIPES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "constants.h"

void pipes_movement(SDL_Renderer** renderer,pipe_t *pipe, int difficulty);
//Function that initialize the position and the gap height
void init_pipes (pipe_t * pipe, int pos, int difficulty, bool update);

#endif// PIPES_H