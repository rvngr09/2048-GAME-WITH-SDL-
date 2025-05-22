/*
# Copyright (c) 2024, 2025 Roumaissa Hadibi & Amine Benallal 
<roumaissa.hadibi.dev@gmai.com> & <aminebenallalghst@gmail.com>
*/

#ifndef MATRIX_H
#define MATRIX_H
#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
typedef enum{
        cyan,def,dark

    }gc;
   
#define SIZE 4


extern int matrix[SIZE][SIZE];

void updateMatrix(int direction);
void printMatrix();
//void renderMatrix(SDL_Renderer* renderer, int matrix[4][4], TTF_Font* font);
bool matrixchange(int matrixcopy[4][4], int matrix[4][4]);
void renderMatrix(SDL_Renderer* renderer, int matrix[4][4], TTF_Font* font, int windowWidth, int windowHeight, gc gametheme);
void initmatrix(int matrix[4][4]);
#endif