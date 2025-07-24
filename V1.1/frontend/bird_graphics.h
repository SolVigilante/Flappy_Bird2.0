#ifndef BIRD_GRAPHICS_H
#define BIRD_GRAPHICS_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../bird.h"
void draw_bird(SDL_Renderer ** renderer, bird_t * bird); //draws bird
void init_bird(bird_t * bird);//initializes the bird
#endif // BIRD_GRAPHICS_H