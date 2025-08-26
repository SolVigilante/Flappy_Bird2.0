#include "bird.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <math.h>
#include "constants.h"
#include "screen.h"


//Prototypes
static void bird_update(bird_t* bird, char c);
static void flying_physics(bird_t * bird);

//Frontend

//Initializes the bird
void init_bird(SDL_Renderer ** renderer, bird_t * bird){
    bird->bird_height = BIRD_HEIGHT;
    bird->bird_width = BIRD_WIDTH;
    bird->bird_x = SCREEN_WIDTH / 5; // The bird will be at 1/5 of the screen
    bird->bird_y = rand() % (SCREEN_HEIGHT - BIRD_HEIGHT); // The bird will appearr at a random height
    bird->velocity = 0.0f; // Initial velocity
    bird->last_gravity_time = -5001; //Last time the gravity was applied, initialized to a negative value so the first increment cant happen immediately
    bird->acceleration = GRAVITY; // Gravity acceleration   
    bird->space_pressed = false; //Space key is not pressed
    bird->collided = false;
}

//Render the texture of the bird
void draw_bird(SDL_Renderer** renderer, bird_t* bird) {
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
        SDL_RenderCopyEx(*renderer, bird->bird_texture[t], NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the physics of the bird
    }else if(bird->shape == 2){
        SDL_SetTextureAlphaMod(bird->bird_texture2[i], alpha);
        SDL_RenderCopyEx(*renderer, bird->bird_texture2[i], NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the physics of the bird
    }else if(bird->shape ==3){
        SDL_SetTextureAlphaMod(bird->bird_texture3, alpha);
        // Draw the bird as a rectangle
        SDL_RenderCopyEx(*renderer, bird->bird_texture3, NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the physics of the bird
    }else if(bird->shape == BIRD_4){
        SDL_SetTextureAlphaMod(bird->bird_texture4[i], alpha);
        SDL_RenderCopyEx(*renderer, bird->bird_texture4[i], NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the 
    }
}

//Backend

static void bird_update(bird_t* bird, char c){
    switch (c) {
        case FLYING_BIRD: 
            bird->velocity = -GRAVITY/3.0f; // Sets the velocity to a negative value to make the bird fly up
            bird->acceleration = 0.0f; // It sets the acceleration to 0, so it doesn't fall immediately
            if(bird->frame >=40){
                bird->frame = 0;
            }
        case FALLING_BIRD:
            bird->acceleration += GRAVITY*0.05; //It adds a portion of the gravity to the acceleration everio 0.1 seconds 
            break;
        default:
            break; //ignores any other input
    }

}

static void flying_physics(bird_t * bird){
    if(bird->acceleration > GRAVITY){
            bird->acceleration = GRAVITY; // Limit the acceleration to the gravity
        }
        bird->velocity += bird->acceleration*0.7f; //Velocity in function of acceleration
        bird->bird_y += bird->velocity * 0.7f; //position in function of velocity
        if (bird->bird_y <= 0){
            bird->bird_y = 0;
        }
        if ((bird->bird_y + bird->bird_height) >= SCREEN_HEIGHT){
            bird->bird_y = SCREEN_HEIGHT - bird->bird_height;
        }
}

void game_start(char c, bird_t* bird) { 
    flying_physics(bird); 
    bird_update(bird, c); // Updates the bird's state based on input
}