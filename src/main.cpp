#include <SDL_timer.h>
#include "Screen.h"
#include "Swarm.h"
#include <iostream>

Uint32 startTime = 0;
Uint32 endTime = 0;
Uint32 delta = 0;
short fps = 20;
short timePerFrame = 1000/fps; // miliseconds

int main() {

    ps::Screen screen;
    ps::Swarm swarm;

    /*swarm.move(600);
    swarm.move(700);
    swarm.move(800);
    swarm.move(900);
    swarm.move(1000);*/

    while(!screen.quit_program()) {

        if (!startTime) {
            // get the time in ms passed from the moment the program started
            startTime = SDL_GetTicks();
        } else {
            delta = endTime - startTime; // how many ms for a frame
        }

        // if less than 16ms, delay
        if (delta < timePerFrame) {
            SDL_Delay(timePerFrame - delta);
        }

        // Load current particle swarm.
        screen.load_swarm(swarm);

        // Update SDL window with new particle positions and colors.
        screen.update();



        // Manipulate particle positions for next iteration. 
        // Ticks are used to ensure consistent/proportional movement.
        swarm.move(SDL_GetTicks());
        //std::cout<<SDL_GetTicks()<<std::endl;

        // Apply gaussian blur effect.
        screen.box_blur();

        if (endTime>2000)
        swarm.burn_step();


        // if delta is bigger than 16ms between frames, get the actual fps
        if (delta > timePerFrame) {
            fps = 1000 / delta;
        }

        //printf("FPS is: %i \n", fps);

        startTime = endTime;
        endTime = SDL_GetTicks();
    }

    return 0;
}
