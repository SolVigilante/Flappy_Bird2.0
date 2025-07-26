#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Initializes the lifes but in the future should initialize the playerś name and creates its own file
void init_player(SDL_Renderer ** renderer, player_t * player){
    player->score=0;
    player->lives=3;
    player->score_font = TTF_OpenFont("fonts/score.ttf", 32); // font size 32
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

void draw_lives (SDL_Renderer ** renderer, player_t * player){
    SDL_Rect heart_shape = { 5, 5, HEART_WIDTH, HEART_HEIGHT }; //Hearts at the left top corner with a fixed width and height
    // Draw the hearts as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); 
    SDL_RenderCopy(*renderer, player->lives_texture, NULL, &heart_shape);
}

void draw_score(SDL_Renderer ** renderer, player_t * player){
    static char score_text [108]; //Max score: a hundred nines
    sprintf(score_text, "Score: %d", player->score); //makes the score string

    SDL_Color color = {0x82, 0x65, 0x12}; // gold

    //Everytime the text is actualized we need to create the surface and modify the text texture
    SDL_Surface* text_surface = TTF_RenderText_Blended(player->score_font, score_text, color);
    player->score_text_texture = SDL_CreateTextureFromSurface(*renderer, text_surface);

    SDL_FreeSurface(text_surface); // it is not needed anymore

    //Creates a rectangular shape with the text width and height
    SDL_Rect dst_rect = {5, 55, text_surface->w, text_surface->h};
    SDL_RenderCopy(*renderer, player->score_text_texture, NULL, &dst_rect);

}

