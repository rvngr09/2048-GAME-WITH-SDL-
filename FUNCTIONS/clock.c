/*
# Copyright (c) 2024, 2025 Amine Benallal <aminebenallalghst@gmail.com>
*/
#include<windows.h>
#include "clock.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include"button.h"

bool clockStarted = false;


void InitClock(Clock* clock){
    clock->start=0;
    clock->elapsedticks=0;
}



void StartClock(Clock* clock) {
    clock->start = SDL_GetTicks();
}



void updateclock(Clock* clock){
    clock->elapsedticks = SDL_GetTicks() - clock->start;
}




Uint32 getelapsedtime(const Clock* clock){
     return clock->elapsedticks;
}




void ResetClock(Clock* clock) {
    clock->start = SDL_GetTicks(); // Reset to current time
    clock->elapsedticks = 0;            // Reset elapsed time
}




void displayElapsedTime(SDL_Renderer* renderer, TTF_Font* font, Uint32 elapsed_time) {
    // Calculate minutes and seconds
    
    Uint32 sec = (elapsed_time / 1000) % 60;
    Uint32 min = (elapsed_time / 60000);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create the time string
    char timestring[50];
    snprintf(timestring, sizeof(timestring), "Elapsed Time: %02d:%02d", min, sec);

    // Define text color
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    // Render the text to a surface
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, timestring, textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface); // Free the surface after creating the texture

    if (texture == NULL) {
        printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Get the dimensions of the texture
    int texW ,texH ;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

    // Define the destination rectangle for rendering
    int textx=screenWidth / 2 - texW / 2;
    int texty=100;
    SDL_Rect dstRect = {textx, texty , texW, texH}; // Adjust position as needed
    
    // Render the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture); // Clean up the texture after rendering
}







