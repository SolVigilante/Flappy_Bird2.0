#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/time.h>  // gettimeofday
#include "screen.h"

//Function to initialize the screen
//This function will set up the SDL window and renderer
//It will return 0 on success and -1 on failure
int init_screen(SDL_Window** window, SDL_Renderer** renderer) {
    //Initialization of SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return 1;
    }
    //Creates the window
    *window =SDL_CreateWindow("Flappy Bird",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //Verrifies if the window was created successfully
    if(*window == NULL){
            SDL_Log("Could not create window: %s", SDL_GetError());
            SDL_Quit();
            return 1;
    }
    //creates the renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    //Verifies if the renderer was created successfully
    if(*renderer == NULL){
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 1;
    }
    return 0;

}
// Function to clean up SDL resources
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer) {
    //Destroys window and renderer
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);
    // Finalizes SDL
    SDL_Quit();
}
// Function to get the current time in milliseconds
long long current_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}