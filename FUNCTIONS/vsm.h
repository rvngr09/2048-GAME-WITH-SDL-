#ifndef VSM_H
#define VSM_H

#include<stdio.h>
#include<stdlib.h>
#include"mouvments.h"
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include"matrix.h"
#include "machine.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;


//int initSDL(const char *title, int width, int height);
//void setRenderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
//void clearScreen();
//void updateScreen();
//void cleanSDL();
void renderMatrixmvsp(SDL_Renderer* renderer, int matrix[4][4], TTF_Font* font, int windowWidth, int windowHeight , int offset,gc gametheme) ;
void renderTwoMatrices(SDL_Renderer* renderer, int matrix1[4][4], int matrix2[4][4], TTF_Font* font, int windowWidth, int windowHeight, gc gametheme);
//void renderMatrixvsm (int matrix[4][4], int offsetX); 

#endif
