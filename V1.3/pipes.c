#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "pipes.h"
#include "screen.h"

//Frontend
void init_pipes (pipe_t * pipe, int pos){
    pipe->position = pos; //It where pos is
    pipe->gap_height = rand() % (SCREEN_HEIGHT - PIPES_GAP + 1) + 1; // New random gap
}

void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe){
    SDL_Rect down_pipe_shape = { pipe->position, SCREEN_HEIGHT - pipe->gap_height , PIPES_WIDTH, pipe->gap_height}; 
    SDL_Rect up_pipe_shape = { pipe->position, 0, PIPES_WIDTH, SCREEN_HEIGHT - pipe->gap_height - PIPES_GAP}; 
    // Draw the bird as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); // color amarillo
    SDL_RenderCopy(*renderer, pipe->up_pipe_texture, NULL, &up_pipe_shape);
    SDL_RenderCopy(*renderer, pipe->down_pipe_texture, NULL, &down_pipe_shape);
}

//Backend
static void move_pipe (pipe_t *pipe, int pipes_left);
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
