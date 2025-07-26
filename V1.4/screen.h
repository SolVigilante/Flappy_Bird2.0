
#ifndef SCREEN_H
#define SCREEN_H    
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "bird.h"
#include "pipes.h"
#include "player.h"
#define SCREEN_WIDTH 1000 //Width of the screen
#define SCREEN_HEIGHT 800 //Height of the screen
//Function to initialize the screen
//This function will set up the SDL window and renderer
//It will return 0 on success and -1 on failure
int init_screen (SDL_Window** window, SDL_Renderer** renderer);
// Function to clean up SDL resources
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer, bird_t * bird, pipe_t *pipe, player_t * player, SDL_Texture * background_texture) ;
long long current_time_ms(void);
void render_text_simple(SDL_Renderer* renderer, TTF_Font* font, const char* texto, int x, int y, SDL_Color color);
#endif // SCREEN_H
