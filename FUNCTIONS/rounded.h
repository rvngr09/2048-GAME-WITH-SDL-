#ifndef roundedcorner_rect
#define roundedcorner_rect
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
void fillCircleQuarter(SDL_Renderer *renderer, int cx, int cy, int radius, int quarter);
void fillRoundedRect(SDL_Renderer *renderer, SDL_Rect rect, int radius);
#endif