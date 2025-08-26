
#include <stdio.h>
#include <stdlib.h>
#include "history_log.h"
#include "screen.h"
#include "constants.h"

static int compar_asc(const void* el1, const void* el2);

void slot_name(player_t* player, SDL_Renderer ** renderer){
    FILE * file;
    char names [3*MAX_USERNAME_LENGTH + 9]= "";
    char player_name[MAX_USERNAME_LENGTH];
    char num [MAX_USERNAME_LENGTH + 16];
    SDL_Color color = {0xB8, 0x8F, 0x33, 255}; //Gold color for the text 
    int i;

    for(i=1; i<=3; i++){
            switch(i){
                case 1:
                    file = fopen("history_log/first_slot.txt", "a+");
                    break;
                case 2:
                    file = fopen("history_log/second_slot.txt", "a+");
                    break;
                case 3:
                    file = fopen("history_log/third_slot.txt", "a+");
                    break;
            }
            if(file != NULL){
                if(fgets(player_name, sizeof(player_name),file)!=NULL){
                    sprintf(num,"%d:", i);
                    strncat(names, num, sizeof(names)-1);
                    strncat(names, player_name , sizeof(names)-1);
                }
                renderTextCentered(renderer, player->username_font, names, color);
            }  
        
    }
}

void write_history_log(player_t* player){
    FILE* file;
    int buffer[6];
    char text_score[MAX_SCORE];
    char name [MAX_USERNAME_LENGTH];
    int count = 0;
    int aux;
    bool rep_flag;

    //Opens the file
    if(player->slot_info.rewrite== DO_REWRITE){
        file = fopen(player->slot_info.slot, "w");
        fprintf(file, "%s\n", player->username);
        fprintf(file, "%d\n", player->score);
    }else{
        file = fopen(player->slot_info.slot, "r+");
        //Reads the last 5 top scores and stores it in a buffer
        for (int i = 0; i < 6 && fgets(text_score, sizeof(text_score), file) != NULL; i++) {
                if(i==0){
                    buffer[i]=strtol(text_score, NULL, 10);
                    count++;
                }else{
                    aux = strtol(text_score, NULL, 10);
                    for(int j= i-1; j>=0 && rep_flag==false; j--){
                        if(buffer[j]==aux){
                            rep_flag =true;
                        }
                    }
                    if(rep_flag == false){
                        buffer[i] = aux;
                        count++;
                    }else{
                        rep_flag = false;
                    }
                }
        }
        for(int i = 0; i<count; i++){
            if(player->score == buffer[i]){
                rep_flag = true;
            }
        }
        if(rep_flag == false){
            buffer[count]= player->score; //Saves the actual score in he last spot in the array
            count++;
        }

        //Arranges from smallest to biggest
        qsort(buffer, count, sizeof(int), compar_asc);
        
        fclose(file);
        file = fopen(player->slot_info.slot, "w");
        fprintf(file, "%s\n", player->username);
        int limit = (count > 5)? 5: count;
        for (int i=0; i<limit; i++){
            fprintf(file, "%d\n", buffer[i]);
        }
    }
    fclose(file);
}

        

static int compar_asc(const void* el1, const void* el2){
    return  *(int*)el2-*(int*)el1;
}
void get_username(player_t *player){
    FILE * file;
    file = fopen(player->slot_info.slot, "r+");
    fgets(player->username, sizeof(player->username), file);
    fclose(file);
}
/*
    FILE * temp = fopen("history_log/temp.txt", "a+");
    char score_text[MAX_SCORE];
    long last_score;
    long next_score;
    bool is_in_place = false; //Flag to know if the score is in the right place
    char player_name[MAX_USERNAME_LENGTH];
    char buffer [100];
    FILE * file;
    switch(player->slot){
        case FIRST_SLOT:
            file = fopen("history_log/first_slot.txt", "r+");
            break;
        case SECOND_SLOT:
            file = fopen("history_log/second_slot.txt", "r+");
            break;
        case THIRD_SLOT:
            file = fopen("history_log/third_slot.txt", "r+");
            break;
    }
    if(fgets(player_name, MAX_USERNAME_LENGTH, file) != NULL){

        if(strcmp(player_name, player->username)){ //If the player name is not the same as the one in the file
            fputs(player->username, temp);
            fputc('\n', temp);
            fflush(temp);
            while(fgets(buffer, 100, file) != NULL){
                fputs(buffer, temp);
            }
            rewind(temp);
            rewind (file);
            while(fgets(buffer, 100, temp) != NULL){
                fputs(buffer, file);
            }
            fclose(temp);
            remove("history_log/temp.txt");
        }
        rewind(file);
        fseek(file, sizeof(player->username), SEEK_SET);
        while(fgets(score_text, MAX_SCORE, file) != NULL){ //Reads the file until the end
            last_score = strtol(score_text, NULL, 10); //Converts the string to a long integer
            printf("%ld\n",last_score );
        }
        fclose(file);
    
    }*/
