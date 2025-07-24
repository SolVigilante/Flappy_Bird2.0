#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "../pipes.h"
#include "../screen.h"
#include "pipes_graphics.h"

void init_pipes (pipe_t * pipe, int pos){
    pipe->position = pos; //It where pos is
    pipe->gap_height = rand() % (SCREEN_HEIGHT - PIPES_GAP + 1) + 1; // New random gap

}
void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe){
    SDL_Rect down_pipe_shape = { pipe->position, SCREEN_HEIGHT - pipe->gap_height, PIPES_WIDTH, pipe->gap_height}; 
    SDL_Rect up_pipe_shape = { pipe->position, 0, PIPES_WIDTH, SCREEN_HEIGHT - pipe->gap_height - PIPES_GAP}; 
    // Draw the bird as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); // color amarillo
    SDL_RenderCopy(*renderer, pipe->up_pipe_texture, NULL, &up_pipe_shape);
    SDL_RenderCopy(*renderer, pipe->down_pipe_texture, NULL, &down_pipe_shape);
}
