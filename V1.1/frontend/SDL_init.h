#ifndef SDL_INIT_H
#define SDL_INIT_H
#include <SDL2/SDL.h>
//Function to initialize the screen
//This function will set up the SDL window and renderer
//It will return 0 on success and -1 on failure
int init_screen (SDL_Window** window, SDL_Renderer** renderer);
// Function to clean up SDL resources
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer);
#endif // SDL_INIT_H