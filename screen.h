
#ifndef SCREEN_H
#define SCREEN_H    
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"

//Function to initialize the screen
//This function will set up the SDL window and renderer
//It will return 0 on success and -1 on failure
int init_screen (SDL_Window** window, SDL_Renderer** renderer);
// Function to clean up SDL resources
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer, bird_t * bird, pipe_t *pipe, player_t * player, letter_texture_t * letter, SDL_Texture * background_texture); ;
long long current_time_ms(void);
void render_centered_image(SDL_Texture* texture, int height, int width, SDL_Renderer** renderer);
void renderImage(SDL_Texture* texture, int height, int width, double cord_y, double cord_x, SDL_Renderer** renderer);
int renderTextCentered(SDL_Renderer **renderer, TTF_Font *font, const char *text, SDL_Color color);
void init_textures(pipe_t* pipe, bird_t * bird, player_t * player,letter_texture_t* letter_texture,  SDL_Renderer ** renderer);
#endif // SCREEN_H