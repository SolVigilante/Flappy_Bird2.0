#include "bird.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>
#include <math.h>
#include "constants.h"
#include "Frontend/screen.h"


//Prototypes
static void bird_update(bird_t* bird, char c);
static void flying_physics(bird_t * bird);

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

//Backend

static void bird_update(bird_t* bird, char c){
    switch (c) {
        case FLYING_BIRD: 
            bird->velocity = -GRAVITY/3.0f; // Sets the velocity to a negative value to make the bird fly up
            bird->acceleration = 0.0f; // It sets the acceleration to 0, so it doesn't fall immediately
            if(bird->frame >=5){
                bird->frame = 0;
            }
        case FALLING_BIRD:
            if(bird->shape == BIRD_3){
                bird->acceleration += GRAVITY*0.01;
            }else{
                bird->acceleration += GRAVITY*0.04; //It adds a portion of the gravity to the acceleration everio 0.1 seconds 
            }
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

void bird_start(char c, bird_t* bird) { 
    flying_physics(bird); 
    bird_update(bird, c); // Updates the bird's state based on input
}