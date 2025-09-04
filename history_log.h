#ifndef HISTORY_LOG_H
#define HISTORY_LOG_H
#include "constants.h"

void slot_name(player_t* player, SDL_Renderer ** renderer);
void write_TOP5(player_t* player);
void write_history_log(player_t* player);
void get_username(player_t *player);
void top10_scores (player_t * player);
void print_score(player_t* player, SDL_Renderer** renderer, int top);

#endif //HISTORY_LOG_H