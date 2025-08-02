#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "pipes.h"
#include "screen.h"
#include "logic.h"
static void move_pipe (pipe_t *pipe, int pipes_left, int difficulty);

//Frontend
void init_pipes ( pipe_t * pipe, int pos, int difficulty, bool update){
        switch (update){
                case false: //If the pipe is being updated
                        if(difficulty == MEDIUM){
                                pipe->d_pipe = rand() % 7 == 0; // ~15% chance of being dynamic
                                pipe->speed = 2; // Speed of the pipe
                        }else if (difficulty == HARD){
                                pipe->d_pipe = rand() % 2 == 0; // 50% chance of being dynamic
                                pipe->speed = 3; // Speed of the pipe
                        }else{ //EASY difficulty
                                pipe->d_pipe = false; // Always static in easy mode
                                pipe->speed = 1; // Speed of the pipe

                        }
                case true: //If the pipe is being initialized
                        pipe->collided = false; //turn on the flag
                        pipe->has_passed = false; //turn off the flag
                        pipe->bounced = false; //turn off the flag
                        pipe->position = pos; //It where pos is
                        pipe->gap_height = rand() % (SCREEN_HEIGHT - PIPES_GAP + 1) + 1; // New random heiht
                        break; 
        }
}


void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe){
    SDL_Rect down_pipe_shape = { pipe->position, pipe->gap_height + PIPES_GAP, PIPES_WIDTH, SCREEN_HEIGHT-pipe->gap_height-PIPES_GAP}; 
    SDL_Rect up_pipe_shape = { pipe->position, 0, PIPES_WIDTH, pipe->gap_height}; 
    // Draw the bird as a rectangle
    SDL_RenderCopy(*renderer, pipe->up_pipe_texture, NULL, &up_pipe_shape);
    SDL_RenderCopy(*renderer, pipe->down_pipe_texture, NULL, &down_pipe_shape);
}

//Backend
// Main loop
void pipes_movement(SDL_Renderer** renderer, pipe_t *pipe, int difficulty) {
        int i;
        for(i = 0; i<NUM_PIPES; i++){
                move_pipe(pipe+i, NUM_PIPES-i-1,difficulty ); //Moves pipe 
                draw_pipes(renderer, pipe+i); // Draw the pipe in the new position
                if((pipe+i)->d_pipe){
                        if(((pipe+i)-> bounced == false)){ //If the gap is too high
                                (pipe+i)-> gap_height += 1; // Randomly change the gap height
                        }else if((pipe+i)-> bounced == true){
                                (pipe+i)-> gap_height -= 1; // Randomly change the gap height
                        }

                        if((pipe+i)-> gap_height <= SCREEN_HEIGHT/4){
                                (pipe+i)-> bounced = false; //Sets the flag to false
                        }else if( (pipe+i)-> gap_height >= (SCREEN_HEIGHT - PIPES_GAP)/2){ //If the gap is too low
                                (pipe+i)-> bounced = true; //Sets the flag to true
                        }
                                
                }

        }
}
//Moves pipe
static void move_pipe (pipe_t *pipe, int pipes_left, int difficulty) {
        pipe->position -= pipe->speed; // Move pipe one column to the left
        if(pipe->position < -PIPES_WIDTH){
                if(pipes_left == NUM_PIPES-1){
                        init_pipes(pipe, (pipe+pipes_left)->position + GAP_PWP+PIPES_WIDTH, difficulty, true); //If it is the last pipe, it will be initialized with a new position
                }else{
                        init_pipes(pipe, (pipe+pipes_left)->position + (NUM_PIPES - pipes_left)*(GAP_PWP + PIPES_WIDTH), difficulty, true);
                }
                
       }

}