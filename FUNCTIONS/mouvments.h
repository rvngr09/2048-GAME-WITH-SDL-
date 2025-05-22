/*
# Copyright (c) 2024, 2025  ismail ziad <ziad0040@gmail.com>

*/

#ifndef MOUVMENTS_SCORE
#define MOUVMENTS_SCORE
#include <SDL2/SDL.h>
#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>
int a_droite(int M[4][4]);
void deplacer_vers_droite(int M[4][4]);
int double_vers_droite(int M[4][4]);
int a_gauche(int M[4][4]);
void deplacer_vers_gauche(int M[4][4]);
int double_vers_gauche(int M[4][4]);
void deplacer_vers_haut(int M[4][4]);
int double_vers_haut(int M[4][4]);
int en_bas(int M[4][4]);
int double_vers_bas(int M[4][4]);
void deplacer_vers_bas(int M[4][4]);

int en_haut(int M[4][4]);

#endif