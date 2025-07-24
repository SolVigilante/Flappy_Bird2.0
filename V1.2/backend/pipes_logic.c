#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../pipes.h"
#include "../screen.h"
#include "pipes_logic.h"
#include "frontend/pipes_graphics.h"

static void move_pipe (pipe_t *pipe, int pipes_left);
// Main loop
void pipes_movement(SDL_Renderer** renderer, pipe_t *pipe, int num_pipes) {
        int i;
        for(i = 0; i<num_pipes; i++){
                move_pipe(pipe+i, num_pipes-i); //Moves pipe 
                draw_pipes(renderer, pipe+i); // Draw the pipe in the new position

        }
}
//Moves pipe
static void move_pipe (pipe_t *pipe, int pipes_left){
        pipe->position -= 1; // Move pipe one column to the left
        if(pipe->position < -PIPES_WIDTH){
                init_pipes(pipe, (pipe+pipes_left-1)->position + GAP_PWP);
                
       }

}