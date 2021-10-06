#pragma once
#include "Particle.hpp"
#include <SDL2/SDL.h>
using namespace std;

class Player : public Particle {
    int health;
    double moveForce = 1;

    //
    SDL_KeyCode moveKeys[4] = {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT};






};