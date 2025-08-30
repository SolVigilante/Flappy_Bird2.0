#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <sys/time.h>  // gettimeofday
#include "screen.h"
#include "constants.h"

//Function to initialize the screen
//This function will set up the SDL window and renderer
//It will return 0 on success and -1 on failure
int init_screen(SDL_Window** window, SDL_Renderer** renderer) {
    //Initialization of SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return 1;
    }
    //Creates the window
    *window =SDL_CreateWindow("Flappy Bird",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //Verrifies if the window was created successfully
    if(*window == NULL){
            SDL_Log("Could not create window: %s", SDL_GetError());
            SDL_Quit();
            return 1;
    }
    //creates the renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    //Verifies if the renderer was created successfully
    if(*renderer == NULL){
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 1;
    }
    return 0;

}
void init_textures(pipe_t* pipe, bird_t * bird, player_t * player,letter_texture_t* letter_texture,  SDL_Renderer ** renderer){
    //Init bird image
    bird->bird_texture [0]= IMG_LoadTexture(*renderer, "image/bird.png");//Initialize bird image
    bird->bird_texture [1]= IMG_LoadTexture(*renderer, "image/bird_middown.png");//Initialize bird image
    bird->bird_texture [2]= IMG_LoadTexture(*renderer, "image/bird_mid.png");//Initialize bird imag
    bird->bird_texture [3]= IMG_LoadTexture(*renderer, "image/bird_midup.png");//Initialize bird imagee
    bird->bird_texture [4]= IMG_LoadTexture(*renderer, "image/bird_up.png");//Initialize bird image

    bird->bird_texture3 [0]= IMG_LoadTexture(*renderer, "image/bird3.png");//Initialize bird image
    bird->bird_texture3 [1]= IMG_LoadTexture(*renderer, "image/bird3_middown.png");//Initialize bird image
    bird->bird_texture3 [2]= IMG_LoadTexture(*renderer, "image/bird3_mid.png");//Initialize bird imag
    bird->bird_texture3 [3]= IMG_LoadTexture(*renderer, "image/bird3_midup.png");//Initialize bird imagee

    bird->bird_texture2[0]= IMG_LoadTexture(*renderer, "image/bird2.png");//Initialize bird image
    bird->bird_texture2[1]= IMG_LoadTexture(*renderer, "image/bird2_middle.png");
    bird->bird_texture2[2]= IMG_LoadTexture(*renderer, "image/bird2_up.png");

    bird->bird_texture4[0] = IMG_LoadTexture(*renderer, "image/bird4.png");
    bird->bird_texture4[1] = IMG_LoadTexture(*renderer, "image/bird4_mid.png");
    bird->bird_texture4[2] = IMG_LoadTexture(*renderer, "image/bird4_up.png");
    for(int i = 0; i<5; i++){
        SDL_SetTextureBlendMode(bird->bird_texture[i], SDL_BLENDMODE_BLEND); //enables transparecy
    }
    for(int i = 0; i<4; i++){
        SDL_SetTextureBlendMode(bird->bird_texture3[i], SDL_BLENDMODE_BLEND); //enables transparecy
    }
    for(int i =0; i<3; i++){
        SDL_SetTextureBlendMode(bird->bird_texture2[i], SDL_BLENDMODE_BLEND); //enables transparecy
        SDL_SetTextureBlendMode(bird->bird_texture4[i], SDL_BLENDMODE_BLEND); //enables transparecy
    }

    //Init pipes textures
    for(int i=0; i<NUM_PIPES; i++){
        //Initialize the top pipe image
        (pipe+i)->up_pipe_texture= IMG_LoadTexture(*renderer, "image/up_pipe.png");
        (pipe+i)->down_pipe_texture= IMG_LoadTexture(*renderer, "image/down_pipe.png");
    }
    for(int i=0; i<NUM_PIPES; i++){
        (pipe+i)->up_pipe_texture3= IMG_LoadTexture(*renderer, "image/pipe_up3.png");
        (pipe+i)->down_pipe_texture3= IMG_LoadTexture(*renderer, "image/pipe_down3.png");
    }
     for(int i=0; i<NUM_PIPES; i++){
        (pipe+i)->up_pipe_texture2= IMG_LoadTexture(*renderer, "image/up2.png");
        (pipe+i)->down_pipe_texture2= IMG_LoadTexture(*renderer, "image/down2.png");
    }

    for(int i=0; i<NUM_PIPES; i++){
        (pipe+i)->up_pipe_texture4= IMG_LoadTexture(*renderer, "image/pipe_up4.png");
        (pipe+i)->down_pipe_texture4= IMG_LoadTexture(*renderer, "image/pipe_down4.png");
    }
    //Init player fonts and textures
    int err = 0; //Error flag
    //Initialize username font
    player->username_font = TTF_OpenFont("fonts/username.ttf", 24);
    if (!player->username_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        err = 1;
    }
    //Initialize username ttexture
    player->username_texture = IMG_LoadTexture(*renderer, "image/Enter_Username.png");
    if (!player->username_texture) {
        SDL_Log("Failed to load username texture: %s", IMG_GetError());
        err = 1;
    }

    if(!err){
        player->score_font = TTF_OpenFont("fonts/score_font.ttf", 100); // font size 50
        player->lives_texture = IMG_LoadTexture(*renderer, "image/3_lives.png");//Initialize bird image
    }
    //Init letter texturesx
    letter_texture->start_texture = IMG_LoadTexture(*renderer, "image/start.png");//Initialize the image of "Press space to start"
    letter_texture->gameover_texture = IMG_LoadTexture(*renderer, "image/GAMEOVER.png");//Initialize the image of GAMEOVER
    letter_texture->speed_up_texture = IMG_LoadTexture(*renderer, "image/speed_up.png");//Initialize the image of "Speed Up!"
    letter_texture->choose_difficulty_texture = IMG_LoadTexture(*renderer, "image/difficulty.png");//Initialize the image of "Choose Difficulty"
    letter_texture->choose_slot_texture = IMG_LoadTexture(*renderer, "image/memory_slot.png");
    letter_texture->choose_rename_texture = IMG_LoadTexture (*renderer, "image/rename_texture.png");
    letter_texture->pause_texture= IMG_LoadTexture(*renderer, "image/Pause.png");
    letter_texture->starting_texture=IMG_LoadTexture(*renderer, "image/Flappy_bird.png");
    letter_texture->rules_texture=IMG_LoadTexture(*renderer, "image/Rules:Commands.png");
    letter_texture->appearance_texture=IMG_LoadTexture(*renderer, "image/appearance.png");
    letter_texture->new_high_score_texture=IMG_LoadTexture(*renderer, "image/new_high_score.png");
}
// Function to clean up SDL resources
//The flag has started is used to know wich resources to free. If tthe ame has stated for even once it will free all the resources. If no i will only free 
//The resources that are needed to choose the difficulty
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer, bird_t * bird, pipe_t *pipe, player_t * player,  letter_texture_t * letter, SDL_Texture * background_texture, SDL_Texture * background_texture2,  SDL_Texture * background_texture3, SDL_Texture * background_texture4) {


        printf("Destroying text input...\n");
        SDL_StopTextInput();
        

        // 2. Destroying graphic resources and fonts
        printf("Destroying username texture...\n");
        SDL_DestroyTexture(player->username_texture);

        printf("Destroying start texture...\n");
        SDL_DestroyTexture(letter->start_texture);

        printf("Destroying gameover texture...\n");
        SDL_DestroyTexture(letter->gameover_texture);

        printf("Destroying speed up texture...\n");
        SDL_DestroyTexture(letter->speed_up_texture);

        printf("Destroying choose difficulty texture...\n");
        SDL_DestroyTexture(letter->choose_difficulty_texture);

        printf("Destroying choose_rename_texture...\n");
        SDL_DestroyTexture(letter->choose_rename_texture);

        printf("Destroying choose slot texture...\n");
        SDL_DestroyTexture(letter->choose_slot_texture);

        printf("Destroying pause texture...\n");
        SDL_DestroyTexture(letter->pause_texture);

        printf("Destroying starting texture..\n");
        SDL_DestroyTexture(letter->starting_texture);

        printf("Destroying rules texture...\n");
        SDL_DestroyTexture(letter->rules_texture);

        printf("Destroying appearance texture..\n");
        SDL_DestroyTexture(letter->appearance_texture);

        printf("Destroying new high score texture..\n");
        SDL_DestroyTexture(letter->new_high_score_texture);

        printf("Destroying background texture...\n");
        SDL_DestroyTexture(background_texture);

        printf("Destroying background texture 2...\n");
        SDL_DestroyTexture(background_texture2);

        printf("Destroying background texture 3...\n");
        SDL_DestroyTexture(background_texture3);

        printf("Destroying background texture 4...\n");
        SDL_DestroyTexture(background_texture4);
        
        
        printf("Destroying username font..\n");
        TTF_CloseFont(player->username_font);

        printf("Destroying bird texture...\n");
        for(int i = 0; i<5; i++){
            SDL_DestroyTexture(bird->bird_texture[i]);
        }
        printf("Destroying bird texture 2...\n");
        for(int i = 0; i<3; i++){
            SDL_DestroyTexture(bird->bird_texture2[i]);
        }

        printf("Destroying bird texture 4...\n");
        for(int i = 0; i<2; i++){
            SDL_DestroyTexture(bird->bird_texture4[i]);
        }

        printf("Destroying bird texture 3..\n");
        for(int i = 0; i<4; i++){
            SDL_DestroyTexture(bird->bird_texture3[i]);
        }

        printf("Destroying pipes textures...\n");
        for (int i = 0; i < NUM_PIPES; i++) {
            SDL_DestroyTexture(pipe[i].up_pipe_texture);
            SDL_DestroyTexture(pipe[i].up_pipe_texture3);
            SDL_DestroyTexture(pipe[i].down_pipe_texture);
            SDL_DestroyTexture(pipe[i].down_pipe_texture3);
            SDL_DestroyTexture(pipe[i].up_pipe_texture2);
            SDL_DestroyTexture(pipe[i].down_pipe_texture2);
            SDL_DestroyTexture(pipe[i].down_pipe_texture4);
            SDL_DestroyTexture(pipe[i].down_pipe_texture4);
        }
        printf("Destroying score font..\n");
        TTF_CloseFont(player->score_font);

        // 3. Destroy render and window
        printf("Destroying renderer..\n");
        SDL_DestroyRenderer(*renderer);

        printf("Destruyendo window...\n");
        SDL_DestroyWindow(*window);
        

        // 4. Close subsystems
        printf("Quiting ttf...\n");
        TTF_Quit();
        
        printf("Quiting image...\n");
        IMG_Quit();
        
        printf("Quiting SDL...\n");
        SDL_Quit();
}



// Function to get the current time in milliseconds
long long current_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}


void render_centered_image(SDL_Texture* texture, int height, int width, SDL_Renderer** renderer){
    SDL_Rect text_shape = { (SCREEN_WIDTH -width)/2, (SCREEN_HEIGHT - height)/2, width, height }; //Hearts at the left top corner with a fixed width and height
    // Draw the hearts as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); 
    SDL_RenderCopy(*renderer, texture, NULL, &text_shape);
}



void renderImage(SDL_Texture* texture, int height, int width,double cord_y, double cord_x, SDL_Renderer** renderer){
    SDL_Rect text_shape = { (SCREEN_WIDTH-width)/cord_x, (SCREEN_HEIGHT - height)/cord_y, width, height }; //Hearts at the left top corner with a fixed width and height
    // Draw the hearts as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); 
    SDL_RenderCopy(*renderer, texture, NULL, &text_shape);
}


int renderTextCentered(SDL_Renderer **renderer, TTF_Font *font, const char *text, SDL_Color color) {
    int err = 0; //Error flag
    //Creates the text surface
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        SDL_Log("error creating the surface for the text: %s", TTF_GetError());
        err = 1;
    }

    //createts the texture from the surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(*renderer, surface);
    if (!texture) {
        SDL_Log("error creating the texture %s", SDL_GetError());
        SDL_FreeSurface(surface);
        err = 1;
    }
    if(!err){
    // Calculates the rectangle to render the text centered
    SDL_Rect rectangle_shape;
    rectangle_shape.w = surface->w;
    rectangle_shape.h = surface->h;
    rectangle_shape.x = (SCREEN_WIDTH - rectangle_shape.w) /2;
    rectangle_shape.y = (SCREEN_HEIGHT - rectangle_shape.h)/2 +100; //100 pixels from the bottom

    // renders the text
    SDL_RenderCopy(*renderer, texture, NULL, &rectangle_shape);

    // frees the surface and texture
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);        //Creates a rectangular shape with the text width and height
    }
    return err;
    
}
