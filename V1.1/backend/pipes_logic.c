#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../pipes.h"
#include "pipes_logic.h"
#include "frontend/pipes_graphics.h"

static void move_pipe (pipe_t *pipe);
// Main loop
void pipes_movement(SDL_Renderer** renderer, pipe_t *pipe) {
        move_pipe(pipe); //Moves pipe 
        draw_pipes(renderer, pipe); // Draw the pipe in the new position
}
//Moves pipe
static void move_pipe (pipe_t *pipe){
      pipe->position -= 1; // Move pipe one column to the left
        if(pipe->position < -PIPES_WIDTH){ // If the pipe moved completely off screen, reset it to the right side
            init_pipes(pipe); //Starts again
        }
}