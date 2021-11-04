#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstring>

using namespace std;

void textOnScreen(SDL_Renderer *ren, string strIn, SDL_Color White){
    TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", 24);
    cout << "Here" << endl;
    cout << "Here" << endl;
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Testing", White); 
    cout << "Here" << endl;
    SDL_Texture* Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
    cout << "Here" << endl;
    SDL_Rect Message_rect; 
    Message_rect.x = 0;  
    Message_rect.y = 0; 
    Message_rect.w = 100;
    Message_rect.h = 100;
    SDL_RenderCopy(ren, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}