#ifndef machine_mode
#define machine_mode
#include<stdio.h>
#include<stdlib.h>
#include"mouvments.h"
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
typedef  enum{
        h,b,g,d
    }ma;
int machine(int matrix[4][4], bool active,ma* move);
int possibilite (int Q[4][4]);
int possibilite_double_gauche(int Q[4][4]);
int possibilite_double_droite(int Q[4][4]);
int possibilite_double_haut(int Q[4][4]);
int possibilite_double_bas(int Q[4][4]);

#endif