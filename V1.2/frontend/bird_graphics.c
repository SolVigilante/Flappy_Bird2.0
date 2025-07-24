#include "../bird.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "bird_graphics.h"
#include "../screen.h"

void init_bird(bird_t * bird){
    int max_x = SCREEN_WIDTH;
    int max_y = SCREEN_HEIGHT;
    bird->bird_height = 100;
    bird->bird_width = 200;
    bird->bird_x = max_x / 5; // The burd will be at 1/5 of the screen
    bird->bird_y = max_y / 2; // The bird will be at the middle of the screen
    bird->velocity = 0.0f; // Initial velocity
    bird->acceleration = GRAVITY; // Gravity acceleration   
}

void draw_bird(SDL_Renderer** renderer, bird_t* bird) {

    SDL_Rect bird_shape = { bird->bird_x, bird->bird_y, bird->bird_width, bird->bird_height }; // fixed size 200x100
    // Draw the bird as a rectangle
    SDL_SetRenderDrawColor(*renderer, 255, 255, 0, 255); // color amarillo
    SDL_RenderCopy(*renderer, bird->bird_texture, NULL, &bird_shape);

}