#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <unistd.h>
#include "bird.h"
#include "backend/flying_logic.h"
#include "frontend/SDL_init.h"
#include "frontend/bird_graphics.h"

int main() {
    // Initialize the screen
    SDL_Window* window ;
    SDL_Renderer* renderer; 
    if(init_screen(&window, &renderer) != 0){
        return 1;
    }
    //Initialize the bird
    bird_t bird;
    init_bird(&bird);

    //initialize the time variable
    long long last_gravity_time = current_time_ms(); //stores the initial time in milliseconds
    long long now;
    //Initialize the background image
    SDL_Texture* background_texture = IMG_LoadTexture(renderer, "flappy_bird_background.jpg");

    //Initialize bird image
    SDL_Texture* bird_texture= IMG_LoadTexture(renderer, "bird.png");

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
        }
            now = current_time_ms();
            if( now - last_gravity_time >= 50) { // Every 50ms, we update the bird's physics
                game_start(FALLING_BIRD, &bird); // Starts the game loop
                last_gravity_time = now;  // Updates the last time gravity was applied
            }
            //Render the current frame
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
            SDL_RenderClear(renderer);

            //Draw Background
            SDL_RenderCopy(renderer, background_texture, NULL, NULL);

            // Draw bird
            draw_bird(bird_texture, &renderer, &bird);

            // Shows the result
            SDL_RenderPresent(renderer);

            SDL_Delay(16); //60 FFPS
    }
    // Clean up SDL resources
    kill_SDL(&window, &renderer);
    return 0;
}


