#include <sys/time.h>  // gettimeofday
#include "../bird.h"
#include "../screen.h"
#include "frontend/bird_graphics.h"
#include "flying_logic.h"

static void bird_update(bird_t* bird, char c);
static void flying_physics(bird_t * bird);

static void bird_update(bird_t* bird, char c){
    switch (c) {
        case FLYING_BIRD: 
            if(bird->velocity > 0.0f){ // If the bird is already flying up, it doesn't do anything
                bird->velocity = -GRAVITY; // Sets the velocity to a negative value to make the bird fly up
                bird->acceleration = 0.0f; // It sets the acceleration to 0, so it doesn't fall immediately
                break;
            }else{
                 bird->acceleration += GRAVITY*0.5; //It adds a portion of the gravity to the acceleration everio 0.1 seconds 
                break;
            }
            
        case FALLING_BIRD:
            bird->acceleration += GRAVITY*0.5; //It adds a portion of the gravity to the acceleration everio 0.1 seconds 
            break;
        default:
            break; //ignores any other input
    }
}

static void flying_physics(bird_t * bird){
    if(bird->acceleration > GRAVITY){
            bird->acceleration = GRAVITY; // Limit the acceleration to the gravity
        }
        bird->velocity += bird->acceleration*0.5f; //Velocity in function of acceleration
        bird->bird_y += bird->velocity * 0.5f; //position in function of velocity
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