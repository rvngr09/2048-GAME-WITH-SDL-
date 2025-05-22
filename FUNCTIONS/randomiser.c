/*

# Copyright (c) 2024, 2025 Amine Benallal <aminebenallalghst@gmail.com>

*/

#include "matrix.h"
#include <stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include"mouvments.h"
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "randomiser.h"
int randomrvennumber(int matrix[4][4],int* gameOverFlag) {
    // Initialize random see
    srand(time(NULL));

    // Define the even numbers we want to choose from 3la hsab la difficulties :)
    int evenNumbers[] = {2, 4};

    
    int emptyTiles[16];  //maximum 16 numero ta3 matrice
    int emptyCount = 0;

    // Find all empty tiles (value == 0)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] == 0) {
                emptyTiles[emptyCount++] = i * 4 + j;  // Store the index of the empty tile
            }
        }
    }

    // If there are no empty tiles, return (do nothing)
    if (emptyCount == 0) {
        *gameOverFlag = 1;
        return -1;
    }

    // Choose a random empty tile index
    int randomTileIndex = emptyTiles[rand() % emptyCount];

    // Convert the index back to row and column
    int row = randomTileIndex / 4;
    int col = randomTileIndex % 4;

    // Choose a random even number (2, 4, 6, or 8)
    int randomEven = evenNumbers[rand() % 2];

    // Place the random even number in the selected empty tile
     
     matrix[row][col] = randomEven;

    // Return 0 to indicate that a number was placed successfully (game is not over)
    return 0;
}