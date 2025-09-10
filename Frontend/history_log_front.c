#include "history_log_front.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "Backend/constants.h"

void print_score(player_t* player, SDL_Renderer** renderer, int top){
    FILE * file;
    int err = 0; 
    int y; //Initial vertical position
    char line[MAX_SCORE]= "";
    
    if(top == TOP_5){
        file = fopen(player->slot_info.slot, "r");
        if(file == NULL){
            printf("Error opening file\n");
            err = 1;
        }else{
            strcpy(line, "TOP PERSONAL SCORES");
            y = SCREEN_HEIGHT / 2 -10;
        }
    }else if(top == TOP_10){
        file = fopen("history_log/Top_10.txt", "r");
        if(file == NULL){
            printf("Error opening file\n");
            err = 1;
        }else{
            strcpy(line, "TOP SCORES");
            y = 70;
        }
    }
    if(err != 1){
        SDL_Color color = {0xB8, 0x8F, 0x33, 255}; //Gold color for the text 
        do{
            SDL_Surface *surface = TTF_RenderText_Solid(player->username_font, line, color);
            if (surface){
                //COnverts surface from text
                SDL_Texture *texture = SDL_CreateTextureFromSurface(*renderer, surface);

                int x = (SCREEN_WIDTH- surface->w)/2; // Width centered 

                SDL_Rect dst = {x, y, surface->w, surface->h}; 
                SDL_RenderCopy(*renderer, texture, NULL, &dst);

                y += surface->h + 5; //Lowers the line

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);
            }
        }while (fgets(line, sizeof(line), file));

        fclose(file);

    }

}