#ifndef BIRD_H
#define BIRD_H
#define GRAVITY 100.0f //Gavity constant
#define BIRD_WIDTH 50
#define BIRD_HEIGHT 50
#define FLYING_BIRD ' ' //Constant that indicates the bird is flying
#define FALLING_BIRD '0' //constant that indicates the bird is falling
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
typedef struct{
    SDL_Texture* bird_texture; //Image for the bird texture
    int bird_height; 
    int bird_width;
    bool floor_collision; //Fla to know whether the bird has collided with the flor recently
    int bird_x; //X position of the bird
    int bird_y; //Y position of the bird
    float velocity; //Velocitty of the bird
    float acceleration; //Acceleration of the bird
}bird_t;
void draw_bird(SDL_Renderer ** renderer, bird_t * bird); //draws bird
void init_bird(SDL_Renderer ** renderer, bird_t * bird);//initializes the bird
void game_start(char c, bird_t* bird); // Function to start the game loop
#endif // BIRD_H
