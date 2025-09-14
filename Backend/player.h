#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"


void init_player(SDL_Renderer ** renderer, player_t * player);

#endif//PLAYER_H