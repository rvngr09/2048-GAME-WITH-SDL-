/*
# Copyright (c) 2024, 2025 Amine Benallal <aminebenallalghst@gmail.com>
*/

#ifndef slide_game_clock
#define slide_game_clock
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

typedef struct  
{
    Uint32 start;
    Uint32 elapsedticks;
    
}Clock;
extern bool clockStarted;
void InitClock(Clock* clock);
void StartClock(Clock* clock);
void updateclock(Clock* clock);
Uint32 getelapsedtime(const Clock* clock);
void ResetClock(Clock* clock);
void displayElapsedTime(SDL_Renderer* renderer , TTF_Font* font ,  Uint32 elapsed_time);


#endif