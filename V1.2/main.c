#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "pipes.h"
#include "bird.h"
#include "backend/flying_logic.h"
#include "frontend/SDL_init.h"
#include "frontend/bird_graphics.h"
#include "backend/pipes_logic.h"
#include "frontend/pipes_graphics.h"


int main() {
    //initialize random
    srand(time(NULL));

    // Initialize the screen
    SDL_Window* window ;
    SDL_Renderer* renderer; 
    if(init_screen(&window, &renderer) != 0){
        return 1;
    }
    //Initialize the bird
    bird_t bird;
    init_bird(&bird);

    //Initialize the pipes
    int i;
    pipe_t pipe[NUM_PIPES];
    for (i=NUM_PIPES; i>0; i--){
        init_pipes(pipe+i-1, SCREEN_WIDTH + i*(GAP_PWP + PIPES_WIDTH));
    }
        

    //initialize the time variable
    long long last_gravity_time = current_time_ms(); //stores the initial time in milliseconds
    long long now;
    //Initialize the background image
    SDL_Texture* background_texture = IMG_LoadTexture(renderer, "image/background.jpg");

    //Initialize bird image
    bird.bird_texture= IMG_LoadTexture(renderer, "image/bird.png");

    //Initialize the pipes array
    for(i=0; i<NUM_PIPES; i++){
        //Initialize the top pipe image
        (pipe+i)->up_pipe_texture= IMG_LoadTexture(renderer, "image/up_pipe.png");

        //Initialize the top pipe image
        (pipe+i)->down_pipe_texture= IMG_LoadTexture(renderer, "image/down_pipe.png");
    }
    
    //Main loop
    bool running = true; //break flag
    bool space_pressed = false;
    SDL_Event event;

    while(running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN://if a key is pressed
                    if (event.key.keysym.sym == SDLK_q) //if case q is pressed it closes the game
                        running = false;

                    if (event.key.keysym.sym == SDLK_SPACE && !space_pressed) { // if space is pressed and not already pressed
                        game_start(FLYING_BIRD, &bird); //updates birds physics for flying
                        space_pressed = true; 

                    }
                    break;

                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        space_pressed = false; //RELEASES THE SPACE KEY
                    }
            }
        }               //Render the current frame
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
            SDL_RenderClear(renderer);

            //Draw Background
            SDL_RenderCopy(renderer, background_texture, NULL, NULL);

             //Draw Background
            SDL_RenderCopy(renderer, background_texture, NULL, NULL);

            pipes_movement(&renderer, pipe, NUM_PIPES);

            // Draw bird
            draw_bird(&renderer, &bird);

            // Shows the result
            SDL_RenderPresent(renderer);

            now = current_time_ms();
            if( now - last_gravity_time >= 100) { // Every 50ms, we update the bird's physics
                game_start(FALLING_BIRD, &bird); // Starts the game loop
                last_gravity_time = now;  // Updates the last time gravity was applied
            }

            SDL_Delay(16); //60 FFPS
    }
    // Clean up SDL resources
    kill_SDL(&window, &renderer);
    return 0;
}


