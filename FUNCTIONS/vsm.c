#include <windows.h>
#include <SDL2/SDL.h>  
#include <stdio.h> 
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include "matrix.h"
#include"mouvments.h"
#include "randomiser.h"
#include<stdio.h>
#include<stdlib.h>
#include"mouvments.h"
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include"matrix.h"
#include "machine.h"
#include "rounded.h"


// hada la page blue 

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

/*int initSDL(const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation SDL: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

void setRenderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void clearScreen() {
    SDL_RenderClear(renderer);
}

void updateScreen() {
    SDL_RenderPresent(renderer);
}

void cleanSDL() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (initSDL("Fenêtre Bleue", 800, 600) != 0) {
        return 1;
    }

    setRenderColor(0, 0, 255, 255);  // Bleu
    clearScreen();
    updateScreen();

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

    cleanSDL();


 // doka rah n'afficher les 2 matrices

    


    return 0;

}
*/
void renderMatrixmvsp(SDL_Renderer* renderer, int matrix[4][4], TTF_Font* font, int windowWidth, int windowHeight , int offset ,gc theme) {
    // Tile size (adjust to your needs)
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

   
    int tileSize;
    if (screenHeight<=1080 && screenWidth<=1920)
    {
        tileSize=140;

    }else if (screenHeight==1600 && screenWidth==2560){
        tileSize=200;

    }
    int grid_size =4 ;
    int grid_w = grid_size*tileSize +(grid_size-1);
    int grid_h = grid_size*tileSize +(grid_size-1);
    int xOffset = (windowWidth - grid_w) / 2 + offset;  // Horizontal padding
    int yOffset = (windowHeight - grid_h) / 2;  // Vertical padding
    int spacing = tileSize/8;  // spacing betweeen tiles

    // Loop through the matrix and render each tile
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int value = matrix[i][j];
            
            // Set color for the tile based on the value
if (theme==def)
{       
  if (value == 0) {
    SDL_SetRenderDrawColor(renderer, 240, 230, 250, 255); // Very light lavender for empty tiles
} else if (value == 2) {
    SDL_SetRenderDrawColor(renderer, 230, 210, 250, 255); // Light lavender for 2
} else if (value == 4) {
    SDL_SetRenderDrawColor(renderer, 220, 190, 245, 255); // Slightly darker lavender for 4
} else if (value == 8) {
    SDL_SetRenderDrawColor(renderer, 210, 170, 240, 255); // Medium lavender for 8
} else if (value == 16) {
    SDL_SetRenderDrawColor(renderer, 200, 150, 235, 255); // Medium-dark lavender for 16
} else if (value == 32) {
    SDL_SetRenderDrawColor(renderer, 190, 130, 230, 255); // Purple for 32
} else if (value == 64) {
    SDL_SetRenderDrawColor(renderer, 180, 110, 225, 255); // Dark purple for 64
} else if (value == 128) {
    SDL_SetRenderDrawColor(renderer, 160, 90, 215, 255);  // Deeper purple for 128
} else if (value == 256) {
    SDL_SetRenderDrawColor(renderer, 140, 70, 205, 255);  // Very deep purple for 256
} else if (value == 512) {
    SDL_SetRenderDrawColor(renderer, 120, 50, 195, 255);  // Near violet for 512
} else if (value == 1024) {
    SDL_SetRenderDrawColor(renderer, 100, 40, 185, 255);  // Violet for 1024
} else if (value == 2048) {
    SDL_SetRenderDrawColor(renderer, 80, 30, 175, 255);   // Dark violet for 2048
} else {
    SDL_SetRenderDrawColor(renderer, 60, 20, 160, 255);   // Almost black purple for numbers >2048
}

}
if (theme==cyan)
{
    if (value == 0) {
    SDL_SetRenderDrawColor(renderer, 220, 220, 250, 255); // Very light blue for empty tiles
} else if (value == 2) {
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255); // Light blue for 2
} else if (value == 4) {
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Sky blue for 4
} else if (value == 8) {
    SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255);  // Steel blue for 8
} else if (value == 16) {
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // Cornflower blue for 16
} else if (value == 32) {
    SDL_SetRenderDrawColor(renderer, 30, 144, 255, 255);  // Dodger blue for 32
} else if (value == 64) {
    SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255);   // Deep sky blue for 64
} else if (value == 128) {
    SDL_SetRenderDrawColor(renderer, 0, 139, 139, 255);   // Dark cyan for 128
} else if (value == 256) {
    SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);   // Teal for 256
} else if (value == 512) {
    SDL_SetRenderDrawColor(renderer, 25, 25, 112, 255);   // Midnight blue for 512
} else if (value == 1024) {
    SDL_SetRenderDrawColor(renderer, 72, 61, 139, 255);   // Dark slate blue for 1024
} else if (value == 2048) {
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);   // Gold for 2048
} else {
    SDL_SetRenderDrawColor(renderer, 255, 69, 0, 255);    // Red for higher numbers
}
}
if (theme==dark)
{
    if (value == 0) {
    SDL_SetRenderDrawColor(renderer, 50, 50, 100, 255); // Very light blue for empty tiles
} else if (value == 2) {
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255); // Light blue for 2
} else if (value == 4) {
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Sky blue for 4
} else if (value == 8) {
    SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255);  // Steel blue for 8
} else if (value == 16) {
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // Cornflower blue for 16
} else if (value == 32) {
    SDL_SetRenderDrawColor(renderer, 30, 144, 255, 255);  // Dodger blue for 32
} else if (value == 64) {
    SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255);   // Deep sky blue for 64
} else if (value == 128) {
    SDL_SetRenderDrawColor(renderer, 0, 139, 139, 255);   // Dark cyan for 128
} else if (value == 256) {
    SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);   // Teal for 256
} else if (value == 512) {
    SDL_SetRenderDrawColor(renderer, 25, 25, 112, 255);   // Midnight blue for 512
} else if (value == 1024) {
    SDL_SetRenderDrawColor(renderer, 72, 61, 139, 255);   // Dark slate blue for 1024
} else if (value == 2048) {
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);   // Gold for 2048
} else {
    SDL_SetRenderDrawColor(renderer, 255, 69, 0, 255);    // Red for higher numbers
}
}
            // Draw the tile
            SDL_Rect tileRect = {xOffset + j * (tileSize+spacing), yOffset + i * (tileSize+spacing), tileSize, tileSize};
            /*SDL_Rect tile = {
                offset_x+col * (tile_size + spacing),
                offset_y+ row * (tile_size + spacing),
                tile_size, tile_size
            };*/
            //SDL_RenderFillRect(renderer, &tileRect);
            int radius=20;
            fillRoundedRect(renderer, tileRect, radius); 

            // If the tile has a value greater than 0, render the number
            if (value > 0) {
                // Create a surface for the number
                char numStr[10];
                snprintf(numStr, sizeof(numStr), "%d", value);

                // Render the text
                SDL_Color textColor = {0, 0, 0, 255};  // Black text
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, numStr, textColor);
                if (textSurface != NULL) {
                    // Create texture from the text surface
                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    if (textTexture != NULL) {
                        // Get the width and height of the text
                        int textWidth = textSurface->w;
                        int textHeight = textSurface->h;

                        // Calculate the position to center the text
                        SDL_Rect textRect = {xOffset + j * (tileSize + spacing) + (tileSize - textWidth) / 2,
                                             yOffset + i * (tileSize + spacing) + (tileSize - textHeight) / 2,
                                             textWidth, textHeight};

                        // Render the text
                        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

                        // Clean up
                        SDL_DestroyTexture(textTexture);
                    }
                    SDL_FreeSurface(textSurface);
                }
            }
        }
    }
}


 void renderTwoMatrices(SDL_Renderer* renderer,int matrix1[4][4], int matrix2[4][4], TTF_Font* font, int windowWidth, int windowHeight , gc gametheme) {
    int tileSize = 140; 
    int spacing = tileSize / 8; 
    int gridWidth = 4 * tileSize + 3 * spacing; 
    int offsetY = (windowHeight - gridWidth) / 2; 

    // Position des deux matrices
    int offsetX1 = (windowWidth - 2 * gridWidth - spacing) / 2; 
    int offsetX2 = offsetX1 + gridWidth + spacing; 
    // l'appel ta3 les 2 matrices
    renderMatrixmvsp(renderer, matrix1,font, windowWidth,windowHeight,600,gametheme);
    renderMatrixmvsp(renderer,matrix2,font,windowWidth,windowHeight, -600,gametheme);

    
    //SDL_RenderPresent(renderer);


      // dok nhat code ta3 jeux la matrice //
    
}



