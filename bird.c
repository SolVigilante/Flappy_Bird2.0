#include "bird.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "screen.h"


//Prototypes
static void bird_update(bird_t* bird, char c);
static void flying_physics(bird_t * bird);

//Frontend

//Initializes the bird
void init_bird(SDL_Renderer ** renderer, bird_t * bird){
    bird->bird_height = BIRD_HEIGHT;
    bird->bird_width = BIRD_WIDTH;
    bird->bird_x = SCREEN_WIDTH / 5; // The burd will be at 1/5 of the screen
    bird->bird_y = SCREEN_HEIGHT / 2; // The bird will be at the middle of the screen
    bird->velocity = 0.0f; // Initial velocity
    bird->acceleration = GRAVITY; // Gravity acceleration   
    bird->floor_collision = false;
    bird->bird_texture= IMG_LoadTexture(*renderer, "image/bird.png");//Initialize bird image
    SDL_SetTextureBlendMode(bird->bird_texture, SDL_BLENDMODE_BLEND); //enables transparecy
}

//Render the texture of the bird
void draw_bird(SDL_Renderer** renderer, bird_t* bird) {

    SDL_Rect bird_shape = { bird->bird_x, bird->bird_y, bird->bird_width, bird->bird_height }; // fixed size 200x100
    // Draw the bird as a rectangle
    SDL_RenderCopyEx(*renderer, bird->bird_texture, NULL, &bird_shape, bird->velocity*0.5f, NULL, SDL_FLIP_NONE); //Enables the physics of the bird

}

//Backend

static void bird_update(bird_t* bird, char c){
    switch (c) {
        case FLYING_BIRD: 
            if(bird->velocity > 0.0f){ // If the bird is already flying up, it doesn't do anything
                bird->velocity = -GRAVITY/3.0f; // Sets the velocity to a negative value to make the bird fly up
                bird->acceleration = 0.0f; // It sets the acceleration to 0, so it doesn't fall immediately
                break;
            }else{
                 bird->acceleration += GRAVITY*0.05; //It adds a portion of the gravity to the acceleration everio 0.1 seconds 
                break;
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