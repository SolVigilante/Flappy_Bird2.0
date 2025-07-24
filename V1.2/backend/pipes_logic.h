#ifndef PIPES_LOGIC_H
#define PIPES_LOGIC_H
#include "../pipes.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
void pipes_movement(SDL_Renderer** renderer,pipe_t *pipe, int num_pipes);
#endif //PIPES_LOGIC_H