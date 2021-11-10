#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstring>

using namespace std;

void SDL_Delay(Uint32 ms);

void textOnScreen(SDL_Renderer *ren){
    string currentTime = to_string(SDL_GetTicks() / 1000);
    const char *text = currentTime.c_str();
    TTF_Font* Sans = TTF_OpenFont("src/OpenSans-Regular.ttf", 24);
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
    SDL_Rect Message_rect; 
    Message_rect.x = 0;  
    Message_rect.y = 0; 
    Message_rect.w = 100;
    Message_rect.h = 100;
    SDL_RenderCopy(ren, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

// with new c.str