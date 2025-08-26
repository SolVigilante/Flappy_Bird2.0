#ifndef PIPES_H
#define PIPES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "constants.h"

void pipes_movement(SDL_Renderer** renderer,pipe_t *pipe, int difficulty);
//Function that initialize the position and the gap height
void init_pipes (pipe_t * pipe, int pos, int difficulty, bool update);
//Function that draws tthe pipes
void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe);
void draw_pipes2(SDL_Renderer ** renderer, pipe_t * pipe);
void draw_pipes3(SDL_Renderer ** renderer, pipe_t * pipe);
void draw_pipes4(SDL_Renderer ** renderer, pipe_t * pipe);
#endif// PIPES_H