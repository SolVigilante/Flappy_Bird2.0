
#ifndef SCREEN_H
#define SCREEN_H    
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "bird.h"
#include "pipes.h"
#include "player.h"

typedef struct{
    SDL_Texture* start_texture; //Texture for the start screen
    SDL_Texture* gameover_texture; //Texture for the game over screen
    SDL_Texture* speed_up_texture; //Texture for the speed up screen
    SDL_Texture* choose_difficulty_texture; //Texture for the choose difficulty screen
}letter_texture_t;

//Function to initialize the screen
//This function will set up the SDL window and renderer
//It will return 0 on success and -1 on failure
int init_screen (SDL_Window** window, SDL_Renderer** renderer);
// Function to clean up SDL resources
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer, bird_t * bird, pipe_t *pipe, player_t * player, letter_texture_t * letter, SDL_Texture * background_texture, bool choose_difficulty) ;
long long current_time_ms(void);
void init_letter_texture(letter_texture_t* letter_texture, SDL_Renderer** renderer);
void render_centered_image(SDL_Texture* texture, int height, int width, SDL_Renderer** renderer);
#endif // SCREEN_H