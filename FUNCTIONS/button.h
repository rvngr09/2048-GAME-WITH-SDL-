/*# Copyright (c) 2024, 2025 Amine Benallal <aminebenallalghst@gmail.com>*/
#ifndef BUTTON_SDL_2024_INCLUDED
#define BUTTON_SDL_2024_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


typedef struct  {
    SDL_Rect rect;
    SDL_Color color;
    SDL_Color hoverColor;
    const char* text;
    bool isHovered;
     bool hoverApplied;
    bool isClicked;
    bool active;
}Button;





void CreateButton(SDL_Renderer* renderer, TTF_Font* font, Button* button , int* h, int* w);
void HandleButtonEvent(SDL_Event* e, Button* button, void (*onClick)(Button*));
void OnButtonClick(Button* button);
void renderMenu(SDL_Renderer* renderer, TTF_Font* font, Button playbutton, Button machinebutton, Button mvspbutton, Button scorebutton, int buttonheight , int buttonwidth);
void renderText(SDL_Renderer *renderer, const char *text, TTF_Font *font, SDL_Color color, int x, int y);
void renderPause(SDL_Renderer* renderer, TTF_Font* font, Button resume,Button replay, Button save, Button main,Button exit , int buttonheight , int buttonwidth);
void analog(SDL_Renderer* renderer, TTF_Font* font, Button up,Button right, Button down, Button left, int buttonheight , int buttonwidth);
#endif