#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "pipes_front.h"
#include "Backend/constants.h"

void draw_pipes(SDL_Renderer ** renderer, pipe_t * pipe){ //Creates the graphics for Pipe 1, it recieves a pointer type pipe
        SDL_Rect down_pipe_shape = { pipe->position, pipe->gap_height + PIPES_GAP, pipe->width, SCREEN_HEIGHT-pipe->gap_height-PIPES_GAP}; //starts texture for the bottom pipe 1
        SDL_Rect up_pipe_shape = { pipe->position, 0, pipe->width, pipe->gap_height}; //starts texture for the top pipe 1
        SDL_RenderCopy(*renderer, pipe->up_pipe_texture, NULL, &up_pipe_shape);
        SDL_RenderCopy(*renderer, pipe->down_pipe_texture, NULL, &down_pipe_shape);
}
void draw_pipes2(SDL_Renderer ** renderer, pipe_t * pipe){//Creates the graphics for Pipe 2, it recieves a pointer type pipe
        SDL_Rect down_pipe_shape = { pipe->position, pipe->gap_height + PIPES_GAP, pipe->width, SCREEN_HEIGHT-pipe->gap_height-PIPES_GAP}; //starts texture for the bottom pipe 2
        SDL_Rect up_pipe_shape = { pipe->position, 0, pipe->width, pipe->gap_height}; //starts texture for the top pipe 2
        SDL_RenderCopy(*renderer, pipe->up_pipe_texture2, NULL, &up_pipe_shape);
        SDL_RenderCopy(*renderer, pipe->down_pipe_texture2, NULL, &down_pipe_shape);
}
void draw_pipes3(SDL_Renderer ** renderer, pipe_t * pipe){//Creates the graphics for Pipe 3, it recieves a pointer type pipe
        SDL_Rect down_pipe_shape = { pipe->position, pipe->gap_height + PIPES_GAP, pipe->width, SCREEN_HEIGHT-pipe->gap_height-PIPES_GAP}; //starts texture for the bottom pipe 3
        SDL_Rect up_pipe_shape = { pipe->position, 0, pipe->width, pipe->gap_height}; //starts texture for the top pipe 3
        SDL_RenderCopy(*renderer, pipe->up_pipe_texture3, NULL, &up_pipe_shape);
        SDL_RenderCopy(*renderer, pipe->down_pipe_texture3, NULL, &down_pipe_shape);
}

void draw_pipes4(SDL_Renderer ** renderer, pipe_t * pipe){//Creates the graphics for Pipe 4, it recieves a pointer type pipe
        SDL_Rect down_pipe_shape = { pipe->position, pipe->gap_height + PIPES_GAP, pipe->width, SCREEN_HEIGHT-pipe->gap_height-PIPES_GAP}; //starts texture for the bottom pipe 4
        SDL_Rect up_pipe_shape = { pipe->position, 0, pipe->width, pipe->gap_height}; //starts texture for the top pipe 4
        SDL_RenderCopy(*renderer, pipe->up_pipe_texture4, NULL, &up_pipe_shape);
        SDL_RenderCopy(*renderer, pipe->down_pipe_texture4, NULL, &down_pipe_shape);
}

//Backend