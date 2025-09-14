#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"

//Initializes the lifes but in the future should initialize the playerś name and creates its own file
void init_player(SDL_Renderer ** renderer, player_t * player){
/*Function that receives a pointer to the renderer and a pointer to the player's structure. Ot initializes the
player and doesn'tt return anything.*/
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
    
