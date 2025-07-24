#ifndef BIRD_H
#define BIRD_H
#define GRAVITY 100.0f //Gavity constant
#define FLYING_BIRD ' ' //Constant that indicates the bird is flying
#define FALLING_BIRD '0' //constant that indicates the bird is falling
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
typedef struct{
    SDL_Texture* bird_texture; //Image for the bird texture
    int bird_height; 
    int bird_width;
    int bird_x; //X position of the bird
    int bird_y; //Y position of the bird
    float velocity; //Velocitty of the bird
    float acceleration; //Acceleration of the bird
}bird_t;
#endif // BIRD_H

