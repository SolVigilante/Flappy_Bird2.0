#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "pipes.h"
#include "screen.h"
static void move_pipe (pipe_t *pipe, int pipes_left);

//Frontend
void init_pipes ( pipe_t * pipe, int pos){
        pipe->collided = false; //turn on the flag
        pipe->has_passed = false; //turn on the flag
        pipe->position = pos; //It where pos is
        pipe->gap_height = rand() % (SCREEN_HEIGHT - PIPES_GAP + 1) + 1; // New random heiht
}

void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe){
    SDL_Rect down_pipe_shape = { pipe->position, pipe->gap_height + PIPES_GAP, PIPES_WIDTH, SCREEN_HEIGHT-pipe->gap_height-PIPES_GAP}; 
    SDL_Rect up_pipe_shape = { pipe->position, 0, PIPES_WIDTH, pipe->gap_height}; 
    // Draw the bird as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); // color amarillo
    SDL_RenderCopy(*renderer, pipe->up_pipe_texture, NULL, &up_pipe_shape);
    SDL_RenderCopy(*renderer, pipe->down_pipe_texture, NULL, &down_pipe_shape);
}

//Backend
// Main loop
void pipes_movement(SDL_Renderer** renderer, pipe_t *pipe) {
        int i;
        for(i = 0; i<NUM_PIPES; i++){
                move_pipe(pipe+i, NUM_PIPES-i-1); //Moves pipe 
                draw_pipes(renderer, pipe+i); // Draw the pipe in the new position

        }
}
//Moves pipe
static void move_pipe (pipe_t *pipe, int pipes_left){
        pipe->position -= 1; // Move pipe one column to the left
        if(pipe->position < -PIPES_WIDTH){
                if(pipes_left == NUM_PIPES-1){
                        init_pipes(pipe, (pipe+pipes_left)->position + GAP_PWP+PIPES_WIDTH);
                }else{
                        init_pipes(pipe, (pipe+pipes_left)->position + (NUM_PIPES - pipes_left)*(GAP_PWP + PIPES_WIDTH));
                }
                
       }

}