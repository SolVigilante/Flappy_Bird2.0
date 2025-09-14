
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "history_log.h"
#include "Frontend/screen.h"
#include "constants.h"

static int compar_desc(const void* el1, const void* el2);
static int compar_score(const void* score1, const void* score2);

void slot_name(player_t* player, SDL_Renderer ** renderer){
/*Function thatt receives a pointer to the player and a pointer to the renderer. It gets the three
usernames of the three memory slots. It prints the three usernames in the screen. It doesn't return anything.*/
    FILE * file;
    char names [3*MAX_USERNAME_LENGTH + 9]= "";
    char player_name[MAX_USERNAME_LENGTH];
    char num [MAX_USERNAME_LENGTH + 16];
    SDL_Color color = {0xB8, 0x8F, 0x33, 255}; //Gold color for the text 
    int i;

    for(i=1; i<=3; i++){
            switch(i){ //Opens the three files
                case 1:
                    file = fopen("history_log/first_slot.txt", "r");
                    break;
                case 2:
                    file = fopen("history_log/second_slot.txt", "r");
                    break;
                case 3:
                    file = fopen("history_log/third_slot.txt", "r");
                    break;
            }
            if(file != NULL){ // it passes the usernamename of the file to a string
                if(fgets(player_name, sizeof(player_name),file)!=NULL){
                    sprintf(num,"%d:", i);
                    strncat(names, num, sizeof(names)-1);
                    strncat(names, player_name , sizeof(names)-1);
                    fclose(file);
                }
            }  
        
    }
    renderTextCentered(renderer, player->username_font, names, color);
}

void write_history_log( player_t * player){
/*Function that receives a pointer to the player structure and writes the history log with the player's
username, the score and the time. It doesn't return anything.*/
    time_t t;               // struct for time in seconds
    struct tm *info;        // sctruct width date and time info
    time(&t); //Get the current time
    info = localtime(&t); //Convert to local time

    FILE* file;
    file = fopen("history_log/History_log.txt", "a");
    if(file != NULL){
        fprintf(file, "%s %d %s", player->username, player->score, asctime(info)); //writes in the archive the username, score and date 
        fclose(file);
    }
}

void write_TOP5(player_t* player){
/*Function that receives a pointer to the player's strucure. It organizes the top 5 personal bes scores
It doesn't resturn anything. */
    FILE* file;
    int buffer[6];
    char text_score[MAX_SCORE];
    int count = 0;
    int aux;
    bool rep_flag;

    //Opens the file
    if(player->slot_info.rewrite== DO_REWRITE){
        file = fopen(player->slot_info.slot, "w");
        fprintf(file, "%s\n", player->username);
        fprintf(file, "%d\n", player->score);
        player->new_high_score_flag = true;
    }else{
        file = fopen(player->slot_info.slot, "r+");
        //Reads the last 5 top scores and stores it in a buffer
        for (int i = -1; i < TOP_5 && fgets(text_score, sizeof(text_score), file) != NULL; i++) {
            //Ignores the username    
            if(i == 0){
                aux = strtol(text_score, NULL, 10);
                buffer[i]= aux;
                count++;
            }else if(i> 0){
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
        qsort(buffer, count, sizeof(int), compar_desc);

        if(player->score == buffer[0]){ //If the score is the highest it has already been saved in the file
            player->new_high_score_flag = true;
        }
        
        fclose(file);
        file = fopen(player->slot_info.slot, "w");
   
        int limit = (count > TOP_5)? TOP_5: count;
        player->username[strcspn(player->username, "\n")] = '\0';
        fprintf(file, "%s\n", player->username);
        for (int i=0; i<limit; i++){
            fprintf(file, "%d\n", buffer[i]);
        }
    }
    fclose(file);
    top10_scores(player);
}

void top10_scores (player_t * player){
/*Function that receives a pointer to the player structure and organizes the top 10 scores of all
the players. It doesn't return anything.*/
    FILE * file;
    bool rep_flag = false;
    int i, j, k;
    int count = 0;
    score_info_t score_info[15];
    char text_score[MAX_SCORE];
    int aux_score;


    file = fopen("history_log/Top_10.txt", "r+");

    if(file !=NULL){
         for(i=0; i<TOP_10 && fgets((score_info+i)->name, MAX_USERNAME_LENGTH, file)!=NULL; i++){
            (score_info+i)->name[strcspn((score_info+i)->name, "\n")] = '\0'; //Eliminates the enter ffrom the buffer
            fgets(text_score, MAX_SCORE, file);
            (score_info +i)->score = strtol(text_score, NULL, 10); //stores score from the file
            count++; 
        }
        fclose(file);

        file=fopen(player->slot_info.slot, "r+");
        if(file != NULL){
            for( j= i; j<(i+6) && fgets(text_score, MAX_SCORE, file)!=NULL; j++){
                    rep_flag = false;
                    if(text_score[0] <= '9' && text_score[0] >= '0'){
                        aux_score= strtol(text_score, NULL, 10); //stores score from the file
                        for(k = i-1; k>=0 && !rep_flag; k--){
                            if((score_info+k)->score == aux_score){
                                rep_flag = true;
                            }
                        }
                        if(!rep_flag){
                            strcpy((score_info+count)->name,player->username );
                            //(score_info+count)->name[strcspn((score_info+j)->name, "\n")] = '\0';
                            (score_info +count)->score = aux_score;
                            count++;
                        }
                    }
            }
            fclose(file);    
        }
    }
    qsort(score_info, count, sizeof(score_info_t), compar_score);

    file = fopen("history_log/Top_10.txt", "w");

    if(file != NULL){
        for(i=0; i<10; i++){ //Writes the 10 highest scores in the file
            fprintf(file, "%s\n", (score_info+i)->name);
            fprintf(file, "%d\n", (score_info+i)->score);
        }
    }
    fclose(file);
}

static int compar_score(const void* score1, const void* score2){
/*Function that receives two pointers to score_info structures and compares the scores. It returns
1 if the first score is less than the second, -1 if the first score is greater than the second and 0 if they are equal.*/
    int score_1 = ((score_info_t *)score1)->score;
    int score_2 = ((score_info_t *)score2)->score;
    
    if (score_1 < score_2) return 1;   // descending order
    if (score_1 > score_2) return -1;
    return 0;
}
static int compar_desc(const void* el1, const void* el2){
/*Function that receives two pointers to integers and compares them. It returns the difference between
the second and the first to sort in descending order.*/

    return *(int*)el2- *(int*)el1;
}
void get_username(player_t *player){
/*Function that receives a pointer to the player structure and gets the username of the player
from the corresponding memory slot. It doesn't return anything.*/
    FILE * file;
    file = fopen(player->slot_info.slot, "r+");
    fgets(player->username, sizeof(player->username), file);
    fclose(file);
}