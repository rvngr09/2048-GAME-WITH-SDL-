/*
# Copyright (c) 2024, 2025 Roumaissa Hadibi & Amine Benallal 
<roumaissa.hadibi.dev@gmai.com> & <aminebenallalghst@gmail.com>
*/
#include <windows.h>
#include <stdio.h>
#include "matrix.h"
#include <stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include"mouvments.h"
#include <SDL2/SDL_ttf.h>
#include "randomiser.h"
#include <stdbool.h>
#include "rounded.h"
//#include <windows.h>
int matrix[SIZE][SIZE] = { 0 };


void updateMatrix(int direction) {
    if (direction == 0) {
        en_haut(matrix);
    }
    else if (direction == 1) {
        en_bas(matrix);
    }
    else if (direction == 2) {
        a_droite(matrix);
    }
    else if (direction == 3) {
        a_gauche(matrix);
    }
}

void printMatrix() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}





void renderMatrix(SDL_Renderer* renderer, int matrix[4][4], TTF_Font* font, int windowWidth, int windowHeight ,gc theme) {
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
    int xOffset = (windowWidth - grid_w) / 2;  // Horizontal padding
    int yOffset = (windowHeight - grid_h-150) / 2;  // Vertical padding
    int spacing = tileSize/8;  // spacing betweeen tiles

    // Loop through the matrix and render each tile
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int value = matrix[i][j];
            
          

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
             SDL_Rect backgroundRect = {xOffset + j * (tileSize + spacing), yOffset + i * (tileSize + spacing), tileSize, tileSize};
            int radius = 20; // Rounded corners radius
            fillRoundedRect(renderer, backgroundRect, radius);
            
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

        
    
bool matrixchange(int matrixcopy[4][4], int matrix[4][4]){
                bool flip=true;
                for (int i = 0; i < 4; i++ && flip) {
                    for (int j = 0; j < 4; j++ && flip) {
                        if (matrixcopy[i][j] == matrix[i][j])
                        {
                            flip=true;
                        }else{
                            flip=false;
                        }
                        
                    }
                }
                if (flip)
                {
                   return false;
                }else{
                    return true;
                }
                
                


}


    void initmatrix(int (matrix)[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = 0; // Initialize all elements to 0
        }
    }
    // place 2 numbers
    int gameOverFlag=0;
    if (randomrvennumber(matrix, &gameOverFlag) == -1) {
    printf("Game Over! No empty tiles available.\n");
    }else{
    printf("Placed a number in the matrix.\n");
    }
    if (randomrvennumber(matrix, &gameOverFlag) == -1) {
    printf("Game Over! No empty tiles available.\n");
    }else{
    printf("Placed a number in the matrix.\n");
    }
}
