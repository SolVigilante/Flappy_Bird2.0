#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    int status; 
    int lives;
    SDL_Texture* username_texture;
    SDL_Texture * lives_texture;
    TTF_Font* score_font;
    TTF_Font* username_font;
    SDL_Texture* enter_username_texture;
    SDL_Texture* score_text_texture;
    int score;
}player_t;

int init_player(SDL_Renderer ** renderer, player_t * player);
void update_lives(SDL_Renderer ** renderer, player_t * player);
void draw_lives(SDL_Renderer ** renderer, player_t * player);
void draw_score(SDL_Renderer ** renderer, player_t * player);

#endif