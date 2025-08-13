#ifndef BIRD_H
#define BIRD_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
typedef struct{
    SDL_Texture* bird_texture; //Image for the bird texture
    int bird_height; 
    int bird_width;
    long long last_collision_time; //Last time the bird collided, initialized to a negative value so the first increment cant happen immediately
    long long last_gravity_time; //Last time the gravity was applied
    bool space_pressed; //Space flag, for key control
    bool floor_collision; //Flag to know whether the bird has collided with the floor
    bool collided; //Flag to know whether the bird has collided
    int bird_x; //X position of the bird
    int bird_y; //Y position of the bird
    float velocity; //Velocitty of the bird
    float acceleration; //Acceleration of the bird
}bird_t;
void draw_bird(SDL_Renderer ** renderer, bird_t * bird); //draws bird
void init_bird(SDL_Renderer ** renderer, bird_t * bird);//initializes the bird
void game_start(char c, bird_t* bird); // Function to start the game loop
#endif // BIRD_H
