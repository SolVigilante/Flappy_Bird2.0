#ifndef LOGIC_H
#define LOGIC_H
#include "bird.h"
#include "pipes.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
bool has_collide(bird_t* bird, pipe_t* pipe);
void game_set(bird_t*bird , pipe_t* pipe, player_t * player, SDL_Renderer ** renderer);
bool has_passed(bird_t * bird, pipe_t * pipe);
#endif //LOGIC_H