#ifndef BIRD_H
#define BIRD_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "constants.h"
void init_bird(SDL_Renderer ** renderer, bird_t * bird);//initializes the bird
void bird_start(char c, bird_t* bird); // Function to start the game loop
#endif // BIRD_H
