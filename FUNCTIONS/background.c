#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

int setBackground(SDL_Renderer *renderer, const char *imagePath) {
    // Load the BMP image as a surface
    SDL_Surface *imageSurface = SDL_LoadBMP(imagePath);
    if (!imageSurface) {
        printf("Failed to load BMP image: %s\n", SDL_GetError());
        return -1;
    }

    // Convert the surface to a texture
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); // Free the surface as it's no longer needed
    if (!backgroundTexture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        return -1;
    }

    // Render the texture to cover the entire screen
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // Clean up
    SDL_DestroyTexture(backgroundTexture);

    return 0; // Success
}