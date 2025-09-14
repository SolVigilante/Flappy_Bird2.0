#ifndef PLAYER_FRONT_H
#define PLAYER_FRONT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Backend/constants.h"
#include "screen.h"

void draw_lives(SDL_Renderer ** renderer, player_t * player);
void draw_score(SDL_Renderer ** renderer, player_t * player);
void update_lives(SDL_Renderer ** renderer, player_t * player);

#endif//PLAYER_FRONT_H