#include <stdbool.h>
#include "bird.h"
#include "pipes.h"
#include "screen.h"
#include "player.h"


//Function that returns true if the bird has collided with he pipe or false if it hasnt
bool has_collide(bird_t* bird, pipe_t* pipe) {

    if (pipe->collided) { //If the bird has already collided wit the pipe it doesnt count
        return false;
    }else if((bird->bird_y == SCREEN_HEIGHT- BIRD_HEIGHT )&& !bird->floor_collision){ //If the bird is on the groundS
        bird->floor_collision = true;
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

//Function ttha returns true if the bird has just passed the pipe
bool has_passed(bird_t * bird, pipe_t * pipe){
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
void game_set(bird_t*bird , pipe_t* pipe, player_t * player, SDL_Renderer ** renderer){
    static int i;
    init_player(renderer, player);
    for (i=NUM_PIPES; i>0; i--){
        init_pipes( pipe+i-1, SCREEN_WIDTH + i*(GAP_PWP + PIPES_WIDTH));
    }
    for(i=0; i<NUM_PIPES; i++){
                //Initialize the top pipe image
                (pipe+i)->up_pipe_texture= IMG_LoadTexture(*renderer, "image/up_pipe.png");

                //Initialize the top pipe image
                (pipe+i)->down_pipe_texture= IMG_LoadTexture(*renderer, "image/down_pipe.png");
        }
    init_bird(renderer, bird);
}

