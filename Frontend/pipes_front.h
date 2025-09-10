
#ifndef PIPES_FRONT_H
#define PIPES_FRONT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "Backend/constants.h"

//Function that draws tthe pipes
void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe);
void draw_pipes2(SDL_Renderer ** renderer, pipe_t * pipe);
void draw_pipes3(SDL_Renderer ** renderer, pipe_t * pipe);
void draw_pipes4(SDL_Renderer ** renderer, pipe_t * pipe);

#endif// PIPES_FRONT_H