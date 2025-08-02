
#ifndef SCREEN_H
#define SCREEN_H    
#include <SDL2/SDL.h>
#define SCREEN_WIDTH 800 //Width of the screen
#define SCREEN_HEIGHT 600 //Height of the screen
//Function to initialize the screen
//This function will set up the SDL window and renderer
//It will return 0 on success and -1 on failure
int init_screen (SDL_Window** window, SDL_Renderer** renderer);
// Function to clean up SDL resources
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer);
long long current_time_ms(void);
#endif // SCREEN_H
