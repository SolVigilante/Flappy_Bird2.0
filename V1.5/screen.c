#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
//The flag has started is used to know wich resources to free. If tthe ame has stated for even once it will free all the resources. If no i will only free 
//The resources that are needed to choose the difficulty
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer, bird_t * bird, pipe_t *pipe, player_t * player,  letter_texture_t * letter, SDL_Texture * background_texture, bool choose_difficulty) {
    switch (choose_difficulty){
        case true: 
                    //Quits sdl image resources
                    SDL_DestroyTexture(background_texture);
                    SDL_DestroyTexture(bird->bird_texture);
                    for(int i = 0; i<NUM_PIPES; i++){
                        SDL_DestroyTexture((pipe+i)->up_pipe_texture);
                        SDL_DestroyTexture((pipe+i)->down_pipe_texture);
                    }
                    SDL_DestroyTexture(player->lives_texture);
                    SDL_DestroyTexture(letter->start_texture);
                    SDL_DestroyTexture(letter->gameover_texture);
                    SDL_DestroyTexture(letter->speed_up_texture);
                    //Quis sdl ttf resources
                    TTF_CloseFont(player->score_font);
                    TTF_Quit();
        case false:
                    //Quits sdl image resources
                    SDL_DestroyTexture(background_texture);
                    SDL_DestroyTexture(letter->choose_difficulty_texture);
                    IMG_Quit();
                    //Destroys window and renderer
                    SDL_DestroyRenderer(*renderer);
                    SDL_DestroyWindow(*window);
                    // Finalizes SDL
                    SDL_Quit();
                    break;

    }

}
// Function to get the current time in milliseconds
long long current_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}
void init_letter_texture(letter_texture_t* letter_texture, SDL_Renderer** renderer){
    letter_texture->start_texture = IMG_LoadTexture(*renderer, "image/start.png");//Initialize the image of "Press space to start"
    letter_texture->gameover_texture = IMG_LoadTexture(*renderer, "image/GAMEOVER.png");//Initialize the image of GAMEOVER
    letter_texture->speed_up_texture = IMG_LoadTexture(*renderer, "image/speed_up.png");//Initialize the image of "Speed Up!"
    letter_texture->choose_difficulty_texture = IMG_LoadTexture(*renderer, "image/difficulty.png");//Initialize the image of "Choose Difficulty"
}

void render_centered_image(SDL_Texture* texture, int height, int width, SDL_Renderer** renderer){
    SDL_Rect text_shape = { (SCREEN_WIDTH -width)/2, (SCREEN_HEIGHT - height)/2, width, height }; //Hearts at the left top corner with a fixed width and height
    // Draw the hearts as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); 
    SDL_RenderCopy(*renderer, texture, NULL, &text_shape);

}
