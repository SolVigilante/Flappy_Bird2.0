#include <stdbool.h>
#include "Backend/bird.h"
#include "pipes.h"
#include "Frontend/screen.h"
#include "logic.h"
#include "player.h"
#include "time.h"
#include "constants.h"



bool has_collide(bird_t* bird, pipe_t* pipe) {
/*Function that returns true if the bird has collided with he pipe or false if it hasnt. It receives
a pointer to the bird structure and a pointer to the pipe strucure.*/

    if(bird->collided){ //If the bird has alredy collided that pipe the score shouldn't increment
        return false;
    }else if((bird->bird_y == SCREEN_HEIGHT- BIRD_HEIGHT )&& !bird->floor_collision){ //If the bird is on the groundS
        return true;
    }else{
        // Verifies the bird is in the horizontal range
        static bool in_horizontal_range;
        in_horizontal_range = (bird->bird_x <= pipe->position + PIPES_WIDTH) && (bird->bird_x + BIRD_WIDTH >= pipe->position);
        // Verifies the bird is in the vertical range
        static bool col_top;
        col_top= pipe->gap_height >= bird->bird_y;
        static bool col_bottom;
        col_bottom = pipe->gap_height + PIPES_GAP <= bird->bird_y + BIRD_HEIGHT;

       return (in_horizontal_range && (col_top || col_bottom));
    }
    return false; // if its not any other case returns false

}


bool has_passed(bird_t * bird, pipe_t * pipe){
/*Function ttha returns true if the bird has just passed the pipe. It receives a pointer to the bird
structure and a pointer to the pipe structure.*/
    if(pipe->has_passed){ //If the bird has alredy passed that pipe the score shouldn't increment
        return false;
    }else{
        static bool before_next;
        before_next = (bird->bird_x < (pipe->position + PIPES_WIDTH + GAP_PWP)); //Analize if the bird is before the next pipe
        static bool after_previous;
        after_previous = (bird->bird_x > (pipe->position + PIPES_WIDTH));//Analize if the bird has passed he pipe

        return before_next && after_previous;
    }
}

//Initialize all the structures
void game_set(bird_t*bird , pipe_t* pipe, player_t * player, letter_texture_t * letter,  SDL_Renderer ** renderer){
/*Function that initialize all the structures. It receives a pointer to the bird structure,
to the pipe struture, to the player structure, tto the letter texture structture and to the renderer.
It doesn't return anything. */
    
    static int i;
    for (i=NUM_PIPES; i>0; i--){
        init_pipes( pipe+i-1, SCREEN_WIDTH + i*(GAP_PWP + PIPES_WIDTH), player->difficulty, false);
    }
    init_bird(renderer, bird);
}




