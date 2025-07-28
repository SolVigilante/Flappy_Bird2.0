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

    //Initialize the images of the phrases
    letter_texture_t letter;

    //initialize the game
    //game_set(&bird, pipe, &player, &letter, HARD, &renderer);

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
    bool inc_flag = false; //Flag to know if the speed has been increased
    long long last_increment_time= -5001; //Last time the speed was increased, initialized to a negative value so the first increment cant happen immediately
    bool choose_difficulty = false; //Flag to know if the user has chosen a difficulty
    bool has_started = false; //Flag to know if the game has started
    int difficulty= -1; //Difficulty variable, initialized to -1 so the user has to choose a difficulty;

    while(running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false; //If the user closes the window the game stops
                    break;

                case SDL_KEYDOWN://if a key is pressed
                    if (event.key.keysym.sym == SDLK_q){ //if case q is pressed it closes the game
                        running = false;
                    }

                    if (event.key.keysym.sym == SDLK_SPACE && !space_pressed && !gameover && choose_difficulty) { // if space is pressed and not already pressed
                        switch (first_key){ //To know if the game can start 
                            case false:
                                first_key= true;
                            case true:
                                game_start(FLYING_BIRD, &bird); //updates birds physics for flying
                                space_pressed = true; 
                                break;
                        }
                    }
                    if(!choose_difficulty && event.key.keysym.sym == SDLK_1){
                        difficulty = EASY; //Sets the difficulty to easy
                    }
                    if(!choose_difficulty && event.key.keysym.sym == SDLK_2){
                        difficulty = MEDIUM; //Sets the difficulty to medium
                    }
                    if(!choose_difficulty && event.key.keysym.sym == SDLK_3){
                        difficulty = HARD; //Sets the difficulty to hard
                    }
    

                    // waits for r key to reset the game
                    if (gameover && event.key.keysym.sym == SDLK_r) {
                        game_set(&bird, pipe, &player, &letter, difficulty, &renderer); // reset
                        first_key= false; //Waits for the user to press space
                        last_increment_time= -5001; //Last time the speed was increased, initialized to a negative value so the first increment cant happen immediately
                        gameover = false; 
                        choose_difficulty = false; //Resets the choose difficulty flag
                        difficulty= -1; //Resets the difficulty variable
                    }
                    break;
                case SDL_KEYUP:
                    if(choose_difficulty){ // prevents the user from pressing space to start the game before choosing a difficulty
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            space_pressed = false; //RELEASES THE SPACE KEY
                        }
                         bird.floor_collision=false;
                    }
                    break;
            }
        } 
        //Render the current frame
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        //Draw Background
        SDL_RenderCopy(renderer, background_texture, NULL, NULL);

            //Draw Background
        SDL_RenderCopy(renderer, background_texture, NULL, NULL);


        if(!gameover && choose_difficulty){ //If the game is not over and the user has chosen a difficulty
            if(!first_key){
                render_centered_image(letter.start_texture, 76, 750, &renderer); //750x76 start image
            }
            //Moves the pipes and draws them
            pipes_movement(&renderer, pipe, HARD);

            //Draws the hearts
            draw_lives(&renderer, &player);
            
            //Draws the score text
            draw_score(&renderer, &player);
            
            now = current_time_ms();
            if((now - last_increment_time <= 5000) ){ //Speed up messsage stays on screen for 5 seconds
                render_centered_image(letter.speed_up_texture, 72, 314, &renderer); //360x100 gameover image
            }

            // Draw bird
            draw_bird(&renderer, &bird);


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
                    inc_flag = false; //Resets the flag so the speed can be increased again
                }
            }
            
            if(player.lives <= 0){
                gameover=true;
            }
            if((player.score)%5 == 0 && player.score != 0 && pipe->speed < SPEED_LIMIT(HARD) && !inc_flag){ //Increases the speed of the pipes every 5 points and top speed is 10
                for(int i=0; i<NUM_PIPES; i++){
                    (pipe+i)->speed++; //Increases the speed of the pipes every 5 frames
                }
                inc_flag = true; //Sets the flag so the speed is not increased again
                last_increment_time = current_time_ms(); //Updates the time of the last increment
            }

        }else if(gameover){
            render_centered_image(letter.gameover_texture, 100, 360, &renderer); //360x100 gameover image
            // Shows the result
        }else if(!choose_difficulty){
            init_letter_texture(&letter, &renderer); //Initializes the letter texture
            render_centered_image(letter.choose_difficulty_texture, 200, 700, &renderer); //360x100 gameover image
            // Shows the result
            if(difficulty != -1){ //If the user has chosen a difficulty
                choose_difficulty = true; //Sets the flag to true so the game can start
                has_started = true; //Sets the flag to true so the game can start
                game_set(&bird, pipe, &player, &letter, difficulty, &renderer); //Resets the game with the new difficulty
            }
        }
        // Shows the result
        SDL_RenderPresent(renderer);
        
        SDL_Delay(16); //60 FFPS   
    }

            
    // Clean up SDL resources
    kill_SDL(&window, &renderer, &bird, pipe, &player, &letter, background_texture, has_started); 
    return 0;

}


