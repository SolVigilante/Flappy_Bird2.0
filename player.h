#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#define HEART_HEIGHT 50
#define HEART_WIDTH 150

typedef struct {
    int lives;
    SDL_Texture * lives_texture;
    TTF_Font* score_font;
    TTF_Font* letters_font;
    SDL_Texture* score_text_texture;
    int score;
}player_t;

void init_player(SDL_Renderer ** renderer, player_t * player);
void update_lives(SDL_Renderer ** renderer, player_t * player);
void draw_lives(SDL_Renderer ** renderer, player_t * player);
void draw_score(SDL_Renderer ** renderer, player_t * player);

#endif