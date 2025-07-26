#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "screen.h"
#include "pipes.h"
#include "bird.h"
#include "logic.h"
#include "player.h"


int main() {
    //initialize random
    srand(time(NULL));

    // Initialize the screen
    SDL_Window* window ;
    SDL_Renderer* renderer; 
    if(init_screen(&window, &renderer) != 0){
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        return 1;   
    }

    //initialize player
    player_t player;

    //Initialize the bird
    bird_t bird;

    //Initialize the pipes
    pipe_t pipe[NUM_PIPES];

    //initialize the game
    game_set(&bird, pipe, &player, &renderer);

    //initialize the time variable
    long long last_gravity_time = current_time_ms(); //stores the initial time in milliseconds
    long long now;

    //Initialize the background image
    SDL_Texture* background_texture = IMG_LoadTexture(renderer, "image/background.jpg");


    
    //Main loop
    bool running = true; //break flag
    bool space_pressed = false; //Space flag, for key control
    bool first_key = false; //Flag o now if the fist key has been pressed
    bool gameover = false;
    SDL_Event event;
    SDL_Color rojo = {0x57, 0x09, 0x0D};

    while(running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false; //If the user closes the window the game stops
                    break;

                case SDL_KEYDOWN://if a key is pressed
                    if (event.key.keysym.sym == SDLK_q) //if case q is pressed it closes the game
                        running = false;

                    if (event.key.keysym.sym == SDLK_SPACE && !space_pressed && !gameover) { // if space is pressed and not already pressed
                        switch (first_key){ //To know if the game can start 
                            case false:
                                first_key= true;
                            case true:
                                game_start(FLYING_BIRD, &bird); //updates birds physics for flying
                                space_pressed = true; 
                                break;
                        }
                        
                    }
                    // Espera una tecla para reiniciar
                    if (gameover && event.key.keysym.sym == SDLK_r) {
                        game_set(&bird, pipe, &player, &renderer); // reset
                        first_key= false; //Waits for the user to press space
                        gameover = false; 
                    }
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        space_pressed = false; //RELEASES THE SPACE KEY
                    }
                    bird.floor_collision=false;
                    break;
            }
        }  
        
        //Render the current frame
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
        SDL_RenderClear(renderer);

        //Draw Background
        SDL_RenderCopy(renderer, background_texture, NULL, NULL);

            //Draw Background
        SDL_RenderCopy(renderer, background_texture, NULL, NULL);


        if(!gameover){
            if(!first_key){
                render_text_simple(renderer, player.score_font, "Press space key to start", SCREEN_WIDTH/2 - 25*10, SCREEN_HEIGHT/2 -20 , rojo); //red Text centered
            }
            //Moves the pipes and draws them
            pipes_movement(&renderer, pipe);

            //Draws the hearts
            draw_lives(&renderer, &player);
            
            //Draws the score text
            draw_score(&renderer, &player);

            // Draw bird
            draw_bird(&renderer, &bird);

            // Shows the result
            SDL_RenderPresent(renderer);

            now = current_time_ms();
            if(( now - last_gravity_time >= 100) && first_key) { // Every 50ms, we update the bird's physics only if the firstt key has been pressed
                game_start(FALLING_BIRD, &bird); // Starts the game loop
                last_gravity_time = now;  // Updates the last time gravity was applied
            }

            for(int i=0; i<NUM_PIPES; i++){
                if(has_collide(&bird, pipe+i)){
                    (pipe+i)->collided= true;
                    player.lives--;
                    update_lives(&renderer, &player);
                }
                if(has_passed(&bird, pipe+i)){
                    player.score++;
                    (pipe+i)->has_passed= true;
                }
            }
            
            if(player.lives <= 0){
                gameover=true;
            }
        }else{
            render_text_simple(renderer, player.score_font, "GAME OVER", SCREEN_WIDTH/2 - 10*10, SCREEN_HEIGHT/2 -20, rojo); //red Text, 10 is aproximately the fonts height
            render_text_simple(renderer, player.score_font, "Press r key to restart or q to quit", SCREEN_WIDTH/2 - 35*10 , SCREEN_HEIGHT/2 +20, rojo); //red Text, 10 is aproximately the fonts height
            // Shows the result
            SDL_RenderPresent(renderer);
        }
        SDL_Delay(16); //60 FFPS   
    }

            
    // Clean up SDL resources
    kill_SDL(&window, &renderer, &bird, pipe, &player, background_texture);
    return 0;

}


