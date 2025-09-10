#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"

//Initializes the lifes but in the future should initialize the playerś name and creates its own file
void init_player(SDL_Renderer ** renderer, player_t * player){
    //Initialize the player
    player->next_speed_up = 5; //Next score to increase the speed
    player->step = 5; //Step variable to increase the speed up every 5 points
    player->difficulty = START_DIFFICULTY; //Difficulty variable, initialized to -1 so the user has to choose a difficulty;
    player->new_high_score_flag = false;
    player->score=0;
    player->lives=3;
    player->score_font = TTF_OpenFont("fonts/score_font.ttf", 100); // font size 50
    player->lives_texture = IMG_LoadTexture(*renderer, "image/3_lives.png");//Initialize bird image
}
    


void update_lives(SDL_Renderer ** renderer, player_t * player){
    if (player->lives == 2){
        player->lives_texture = IMG_LoadTexture(*renderer, "image/2_lives.png");//Bird image changes to the one with 2 hearts
    }else if(player->lives == 1){
        player->lives_texture = IMG_LoadTexture(*renderer, "image/1_live.png");//Bird image changes to the one with 1 heart
    }else if(player->lives <= 0){
         player->lives_texture = IMG_LoadTexture(*renderer, "image/0_lives.png");//Bird image changes to the one with 0 hearts
    }
}
