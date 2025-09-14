#include "bird_front.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Backend/constants.h"
#include "Backend/time.h"

//Render the texture of the bird
void draw_bird(SDL_Renderer** renderer, bird_t* bird) {//Function that draws the bird, it recieves a bird pointer
    int alpha; // Alpha value for transparency
    bird->frame++;
    int i = (bird->frame / 10) % 3;
    int t = (bird->frame / 10) % 5; //dsp lo saco
    float time = (float)(current_time_ms() % 1000) / 1000.0f; // Time in seconds for the sine wave
    SDL_Rect bird_shape = { bird->bird_x, bird->bird_y, bird->bird_width, bird->bird_height }; // fixed size 200x100
    if(bird->collided){ //If the bird has collided with a pipe
        alpha = (int)(127.5f * (1.0f + sinf(2 * M_PI * time))); // sin between 0 y 255

    }else{
        alpha = 255; // If the bird has not collided, it is fully opaque
    }
    if(bird->shape == 1){
        SDL_SetTextureAlphaMod(bird->bird_texture[t], alpha);
        // Draw the bird as a rectangle
        SDL_RenderCopyEx(*renderer, bird->bird_texture[t], NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the physics of the bird1
    }else if(bird->shape == 2){
        SDL_SetTextureAlphaMod(bird->bird_texture2[i], alpha);
        SDL_RenderCopyEx(*renderer, bird->bird_texture2[i], NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the physics of the bird2
    }else if(bird->shape ==3){
        SDL_SetTextureAlphaMod(bird->bird_texture3[i], alpha);
        SDL_RenderCopyEx(*renderer, bird->bird_texture3[i], NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the physics of the bird3
    
    }else if(bird->shape == BIRD_4){
        SDL_SetTextureAlphaMod(bird->bird_texture4[i], alpha);
        SDL_RenderCopyEx(*renderer, bird->bird_texture4[i], NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the physics of the bird4
    }
}
