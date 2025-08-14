#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
// Function to clean up SDL resources
//The flag has started is used to know wich resources to free. If tthe ame has stated for even once it will free all the resources. If no i will only free 
//The resources that are needed to choose the difficulty
void kill_SDL (SDL_Window** window, SDL_Renderer** renderer, bird_t * bird, pipe_t *pipe, player_t * player,  letter_texture_t * letter, SDL_Texture * background_texture, int game_progress) {


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

        printf("Destroying background texture...\n");
        SDL_DestroyTexture(background_texture);
        
        printf("Destroying username font..\n");
        TTF_CloseFont(player->username_font);

        if(game_progress == CLOSE_AT_PLAYING || game_progress == CLOSE_AT_GAMEOVER){
            printf("Destroying bird texture...\n");
            SDL_DestroyTexture(bird->bird_texture);

            printf("Destroying pipes textures...\n");
            for (int i = 0; i < NUM_PIPES; i++) {
                SDL_DestroyTexture(pipe[i].up_pipe_texture);
                SDL_DestroyTexture(pipe[i].down_pipe_texture);
            }
            printf("Destroying score font..\n");
            TTF_CloseFont(player->score_font);
            
        }

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

/*
    if(has_started == false)
    
    // 1. Detener entrada de texto si estaba activa

    SDL_StopTextInput();
    printf("Destruyendo text...\n");

    // 2. Destruir recursos gráficos y de fuentes
    SDL_DestroyTexture(bird->bird_texture);
    printf("Destruyendo bird texture...\n");
    for (int i = 0; i < NUM_PIPES; i++) {
        SDL_DestroyTexture(pipe[i].up_pipe_texture);
        SDL_DestroyTexture(pipe[i].down_pipe_texture);
    }
    printf("Destruyendo pipes texture...\n");
    SDL_DestroyTexture(player->lives_texture);
    printf("Destruyendo lives texture...\n");
    SDL_DestroyTexture(player->username_texture);
    printf("Destruyendo username texture...\n");
    
    SDL_DestroyTexture(player->score_text_texture);
    printf("Destruyendo score texture...\n");
    
    

    SDL_DestroyTexture(letter->start_texture);
    printf("Destruyendo start texture...\n");
    SDL_DestroyTexture(letter->gameover_texture);
    printf("Destruyendo gameover texture...\n");
    SDL_DestroyTexture(letter->speed_up_texture);
    printf("Destruyendo speed up texture...\n");
    SDL_DestroyTexture(letter->choose_difficulty_texture);
    printf("Destruyendo choose texture...\n");

    SDL_DestroyTexture(background_texture);
    printf("Destruyendo background texture...\n");

    TTF_CloseFont(player->score_font);
    printf("Destruyendo score font..\n");
    TTF_CloseFont(player->username_font);
    printf("Destruyendo username font..\n");
    TTF_CloseFont(player->letters_font);
    printf("Destruyendo letters font...\n");

    // 3. Destruir renderer y ventana
    SDL_DestroyRenderer(*renderer);
    printf("Destruyendo renderer..\n");
    SDL_DestroyWindow(*window);
    printf("Destruyendo window...\n");

    // 4. Cerrar subsistemas
    TTF_Quit();
    printf("Destruyendo ttf quit...\n");
    IMG_Quit();
    printf("Destruyendo img quit...\n");
    SDL_Quit();
*/
}



// Function to get the current time in milliseconds
long long current_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}
void init_letter_texture(letter_texture_t* letter_texture, SDL_Renderer** renderer){
    letter_texture->start_texture = IMG_LoadTexture(*renderer, "image/start.png");//Initialize the image of "Press space to start"
    letter_texture->gameover_texture = IMG_LoadTexture(*renderer, "image/GAMEOVER.png");//Initialize the image of GAMEOVER
    letter_texture->speed_up_texture = IMG_LoadTexture(*renderer, "image/speed_up.png");//Initialize the image of "Speed Up!"
    letter_texture->choose_difficulty_texture = IMG_LoadTexture(*renderer, "image/difficulty.png");//Initialize the image of "Choose Difficulty"
}

void render_centered_image(SDL_Texture* texture, int height, int width, SDL_Renderer** renderer){
    SDL_Rect text_shape = { (SCREEN_WIDTH -width)/2, (SCREEN_HEIGHT - height)/2, width, height }; //Hearts at the left top corner with a fixed width and height
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
