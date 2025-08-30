#ifndef LOGIC_H
#define LOGIC_H
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
bool has_collide(bird_t* bird, pipe_t* pipe);
void game_set(bird_t*bird , pipe_t* pipe, player_t * player, letter_texture_t * letter, SDL_Renderer ** renderer);
bool has_passed(bird_t * bird, pipe_t * pipe);
#endif //LOGIC_H