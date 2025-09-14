#include "player_front.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Backend/constants.h"

void draw_lives (SDL_Renderer ** renderer, player_t * player){
//Function that draws lives, it recieves a pointer to player and a renderer
    SDL_Rect heart_shape = { 5, 5, HEART_WIDTH, HEART_HEIGHT }; //Hearts at the left top corner with a fixed width and height
    // Draw the hearts as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); 
    SDL_RenderCopy(*renderer, player->lives_texture, NULL, &heart_shape);
}

void draw_score(SDL_Renderer ** renderer, player_t * player){//Function that draws scores, it recieves a pointer to player and a renderer
    static char score_text [MAX_SCORE]; //Max score: a hundred nines
    sprintf(score_text, "%d", player->score); //makes the score string

    SDL_Color color = {0xC7, 0xA6, 0x24}; // yellow
    //if(bird.shape == BIRD_2){
        //SDL_Color color = {255, 105, 180, 255}; 
    //}

    //Everytime the text is actualized we need to create the surface and modify the text texture
    SDL_Surface* text_surface = TTF_RenderText_Blended(player->score_font, score_text, color); // Creates the surface with the text
    player->score_text_texture = SDL_CreateTextureFromSurface(*renderer, text_surface);

    //Creates a rectangular shape with the text width and height
    SDL_Rect dst_rect = {(SCREEN_WIDTH- text_surface->w)/2 , (SCREEN_HEIGHT - text_surface->h)/5, text_surface->w, text_surface->h};
    SDL_RenderCopy(*renderer, player->score_text_texture, NULL, &dst_rect);
    SDL_FreeSurface(text_surface); // it is not needed anymore
}

void update_lives(SDL_Renderer ** renderer, player_t * player){//Function that updates lives, it recieves a pointer to player and a renderer
    if (player->lives == 2){
        player->lives_texture = IMG_LoadTexture(*renderer, "image/2_lives.png");//Bird image changes to the one with 2 hearts
    }else if(player->lives == 1){
        player->lives_texture = IMG_LoadTexture(*renderer, "image/1_live.png");//Bird image changes to the one with 1 heart
    }else if(player->lives <= 0){
         player->lives_texture = IMG_LoadTexture(*renderer, "image/0_lives.png");//Bird image changes to the one with 0 hearts
    }
}
