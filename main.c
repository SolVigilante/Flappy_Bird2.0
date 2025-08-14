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
#include "constants.h"

static void collision_logic(pipe_t* pipe, bird_t* bird, player_t* player, bool *inc_flag, SDL_Renderer** renderer    );
static void speed_up_logic(pipe_t* pipe, player_t* player, bool *inc_flag, letter_texture_t* letter, SDL_Renderer** renderer);
static void update_bird(bird_t* bird, player_t* player);

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


    //Initialize the background image
    SDL_Texture* background_texture = IMG_LoadTexture(renderer, "image/background.jpg");


    
    //Main loop
    SDL_Event event; //Event variable
    bool running = true; //break flag
    bool inc_flag = false; //Flag to know if the speed has been increased
    int game_progress = CLOSE_AT_USERNAME; //Flag to know if the game has started
    int difficulty = START_DIFFICULTY; //Difficulty variable, initialized to -1 so the user has to choose a difficulty;
    char txtinput[MAX_USERNAME_LENGTH]= ""; //Input variable for the user to choose a difficulty
    bool is_text_input_active = false; //Flag to know if the text input is active

    init_letter_texture(&letter, &renderer); //Initializes the letter texture
    init_player(&renderer, &player); //Initializes the player

    SDL_StartTextInput();
    is_text_input_active = true;

    while(running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false; //If the user closes the window the game stops
                    break;

                case SDL_KEYDOWN://if a key is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE){ //if case q is pressed it closes the game
                        running = false;
                        break;
                    }

                    if (event.key.keysym.sym == SDLK_SPACE && !bird.space_pressed && (player.status == PLAYING || player.status == FIRST_KEY)) { // if space is pressed and not already pressed
                        switch (player.status){ //To know if the game can start 
                            case FIRST_KEY:
                                player.status = PLAYING; //Changes the status to playing
                            case PLAYING:
                                game_start(FLYING_BIRD, &bird); //updates birds physics for flying
                                bird.space_pressed = true; 
                                break;
                        }
                    }
                    if(player.status == CHOOSING_DIFFICULTY && event.key.keysym.sym == SDLK_1){
                        difficulty = EASY; //Sets the difficulty to easy
                    }
                    else if(player.status == CHOOSING_DIFFICULTY && event.key.keysym.sym == SDLK_2){
                        difficulty = MEDIUM; //Sets the difficulty to medium
                    }
                    else if(player.status == CHOOSING_DIFFICULTY && event.key.keysym.sym == SDLK_3){
                        difficulty = HARD; //Sets the difficulty to hard
                    }
    

                    // waits for r key to reset the game
                    if (player.status==GAMEOVER && event.key.keysym.sym == SDLK_r) {
                        init_player(&renderer, &player); //Reinitializes the player
                        difficulty = START_DIFFICULTY;
                    }

                    if(player.status == CHOOSING_USERNAME){
                        if(event.key.keysym.sym == SDLK_BACKSPACE && strlen(txtinput) > 0) { //If backspace is pressed and the input is not empty
                            txtinput[strlen(txtinput) - 1] = '\0'; //Removes the last character from the input
                        }else if(event.key.keysym.sym == SDLK_RETURN) { //If enter is pressed
                            player.status = CHOOSING_DIFFICULTY; //Changes the status to choosing difficulty
                            game_progress = CLOSE_AT_CHOOSE_DIFFICULTY; //Changes the game progress to choosing difficulty
                            strncpy(player.username, txtinput, MAX_USERNAME_LENGTH - 1);
                        }
                    }
                    break;
                case SDL_KEYUP:
                    if(player.status != CHOOSING_DIFFICULTY){ // prevents the user from pressing space to start the game before choosing a difficulty
                        if (event.key.keysym.sym == SDLK_SPACE) {
                            bird.space_pressed = false; //RELEASES THE SPACE KEY
                        }
                         bird.floor_collision=false;
                    }
                    break;
                case SDL_TEXTINPUT:
                    if (player.status == CHOOSING_USERNAME && is_text_input_active) {
                        size_t len = strlen(txtinput);
                        size_t remaining = MAX_USERNAME_LENGTH - len - 1; // -1 for the null terminator
                        if (remaining > 0) {
                            strncat(txtinput, event.text.text, remaining);
                        }
                    }
                    break;
                }
        }
        if(running == false){
            break; //If the user closes the window, the game stops
        }else if(running == true){
            //Render the current frame
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
            SDL_RenderClear(renderer);

            //Draw Background
            SDL_RenderCopy(renderer, background_texture, NULL, NULL);

                //Draw Background
            SDL_RenderCopy(renderer, background_texture, NULL, NULL);

           
             if(player.status == CHOOSING_USERNAME && is_text_input_active){ //If the user is choosing a username
                SDL_Color color = {255, 255, 255, 255}; //White color for the text
                render_centered_image(player.username_texture, 61, 536, &renderer); //750x76 start image
                if(strlen(txtinput)>0 && is_text_input_active){ //If the user has entered a username and the text input is active
                    renderTextCentered(&renderer, player.username_font, txtinput, color); //Renders the text input in the center of the screen
                }
                
            }

            if(player.status == PLAYING || player.status==FIRST_KEY){ //If the game is not over and the user has chosen a difficulty
                if(player.status==FIRST_KEY){
                    render_centered_image(letter.start_texture, 76, 750, &renderer); //750x76 start image
                }
                
                pipes_movement(&renderer, pipe, HARD);

                
                draw_lives(&renderer, &player);
                
                
                draw_score(&renderer, &player);
        
                update_bird(&bird, &player); //Updates the bird's physics

                
                draw_bird(&renderer, &bird);

                collision_logic(pipe, &bird, &player, &inc_flag, &renderer); //Checks for collisions and updates the score
                
                speed_up_logic(pipe, &player, &inc_flag, &letter, &renderer); //Increases the speed of the pipes every 5 points
                
                if(player.lives <= 0){
                    player.status = GAMEOVER; //If the player has no lives left, the game is over
                    game_progress= CLOSE_AT_GAMEOVER;
                }

            }else if(player.status == GAMEOVER){ //If the game is over
                render_centered_image(letter.gameover_texture, 100, 360, &renderer); //360x100 gameover image
        
            }else if(player.status == CHOOSING_DIFFICULTY){ //If the user is choosing a difficulty
                render_centered_image(letter.choose_difficulty_texture, 200, 700, &renderer); //360x100 gameover image
                
                if(difficulty != START_DIFFICULTY){ //If the user has chosen a difficulty
                    player.status = FIRST_KEY; 
                    game_progress = CLOSE_AT_PLAYING; //Changes the game progress to playing
                    
                    game_set(&bird, pipe, &player, &letter, difficulty, &renderer); //Resets the game with the new difficulty
                }
            }
            // Shows the result
            SDL_RenderPresent(renderer);
            
            SDL_Delay(16); //60 FFPS   
        }
    }

    // Clean up SDL resources
    kill_SDL(&window, &renderer, &bird, pipe, &player, &letter, background_texture, game_progress); 
    return 0;

}

static void collision_logic(pipe_t* pipe, bird_t* bird, player_t* player, bool *inc_flag, SDL_Renderer** renderer) {
/*FUnctioon that evaluates if here has been a collision or if the score should increase.*/
    for(int i=0; i<NUM_PIPES; i++){
                if(has_collide(bird, pipe+i)){
                    bird->collided= true;
                    player->lives--;
                    update_lives(renderer, player);
                    bird->last_collision_time = current_time_ms(); //Updates the time of the last collision
                }
                if(has_passed(bird, pipe+i)){
                    player->score++;
                    (pipe+i)->has_passed= true;
                    *inc_flag = false; //Resets the flag so the speed can be increased again
                }
            }
}

static void speed_up_logic(pipe_t* pipe, player_t* player, bool *inc_flag, letter_texture_t* letter, SDL_Renderer** renderer) {
/*Function that evaluates if the game should speed up because the player has passed 5 pipes. It also manages
the logic for graphic part. */
    if((player->score)%5 == 0 && player->score != 0 && pipe->speed < SPEED_LIMIT(HARD) && !*inc_flag){ //Increases the speed of the pipes every 5 points and top speed is 10
        for(int i=0; i<NUM_PIPES; i++){
            (pipe+i)->speed++; //Increases the speed of the pipes every 5 frames
        }
        *inc_flag = true; //Sets the flag so the speed is not increased again
        pipe->last_increment_time = current_time_ms(); //Updates the time of the last increment
    }
    long long now = current_time_ms();
    if((now - pipe->last_increment_time <= 5000) && *inc_flag){ //Speed up messsage stays on screen for 5 seconds
        render_centered_image(letter->speed_up_texture, 72, 314, renderer); //360x100 gameover image
    }
}

static void update_bird(bird_t* bird, player_t* player) {
/*FFUnction that updates the birds physics.*/
    long long now = current_time_ms();
    if((now - bird->last_collision_time >= 3000) && bird->collided){
        bird->collided = false; //Resets the collision flag after 3 seconds
    }
    if((now - bird->last_gravity_time >= 100) && player->status != FIRST_KEY) { // Every 100ms, we update the bird's physics only if the firstt key has been pressed
        game_start(FALLING_BIRD, bird); // Starts the game loop
        bird->last_gravity_time = now;  // Updates the last time gravity was applied
    }
}