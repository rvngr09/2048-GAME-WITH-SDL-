/*

# Copyright (c) 2024, 2025 Amine Benallal <aminebenallalghst@gmail.com>

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include"clock.h"
#include "rounded.h"

void CreateButton(SDL_Renderer* renderer, TTF_Font* font, Button* button, int* h, int* w) {
    // Base button size
    int button_w = *w;
    int button_h = *h;

    // Save the center position of the button
    int centerX = button->rect.x + button->rect.w / 2;
    int centerY = button->rect.y + button->rect.h / 2;

    // Apply "pop" effect when hovered
    if (button->isHovered) {
        button_w += 13; // Increase width
        button_h += 13; // Increase height
    }

    // Update the button's dimensions
    button->rect.w = button_w;
    button->rect.h = button_h;

    // Recenter the button
    button->rect.x = centerX - button_w / 2;
    button->rect.y = centerY - button_h / 2;

    // Determine the color based on hover state
    SDL_Color Color = button->isHovered ? button->hoverColor : button->color;

    // Set the render draw color and fill the button rectangle
    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
    int radius = 30;
    fillRoundedRect(renderer, button->rect, radius);

    // Render the button text
    SDL_Color textColor = {255, 255, 255, 255}; // White text
    SDL_Surface* surface = TTF_RenderText_Solid(font, button->text, textColor);
    if (!surface) {
        SDL_Log("Text rendering failed: %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Text texture rendering failed: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Get the dimensions of the text texture
    int textWidth, textHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

    // Center the text within the button
    SDL_Rect textRect = {
        button->rect.x + (button->rect.w - textWidth) / 2,
        button->rect.y + (button->rect.h - textHeight) / 2,
        textWidth,
        textHeight
    };

    // Render the text texture
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // Clean up resources
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}



void HandleButtonEvent(SDL_Event* e, Button* button, void (*onClick)(Button*)) {
    if (!button->active) {
        return; // Skip inactive buttons
    }

    // Get mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Check if the mouse is inside the button bounds
    bool inside = (mouseX > button->rect.x) && (mouseX < button->rect.x + button->rect.w) &&
                  (mouseY > button->rect.y) && (mouseY < button->rect.y + button->rect.h);

    // Update hover state
    if (inside && !button->isHovered) {
        button->isHovered = true; // Mouse entered button
    } else if (!inside && button->isHovered) {
        button->isHovered = false; // Mouse left button
    }

    // Handle click event
    if (inside && e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT) {
        if (onClick) {
            onClick(button);
        }
    }
}



void OnButtonClick(Button* button) {
    
    button->isClicked=false;
    int mousex , mousey;
    SDL_GetMouseState(&mousex, &mousey);
    if(mousex>=button->rect.x && mousex<=button->rect.x +button->rect.w && mousey>= button->rect.y && mousey<= button->rect.y+button->rect.h ){
        button->isClicked=true;
        clockStarted = true;
    }else if (mousex>=button->rect.x && mousex<=button->rect.x +button->rect.w && mousey>= button->rect.y && mousey<= button->rect.y+button->rect.h && button->isClicked==true){
        button->isClicked=false;
        clockStarted = false;
    }
    
    
    
}

void renderMenu(SDL_Renderer* renderer, TTF_Font* font, Button playbutton, Button machinebutton, Button mvspbutton, Button scorebutton , int buttonheight , int buttonwidth) {
    int h = buttonheight, w = buttonwidth;

    CreateButton(renderer, font, &playbutton, &h, &w);
    CreateButton(renderer, font, &machinebutton, &h, &w);
    CreateButton(renderer, font, &mvspbutton, &h, &w);
    CreateButton(renderer, font, &scorebutton, &h, &w);
    
}
void renderPause(SDL_Renderer* renderer, TTF_Font* font, Button resume,Button replay, Button save, Button mainb,Button exit , int buttonheight , int buttonwidth) {
    int h = buttonheight, w = buttonwidth;
    //SDL_SetRenderDrawColor(renderer, 9, 173, 255, 1); // Semi-transparent black
    //SDL_RenderFillRect(renderer, NULL);
    CreateButton(renderer, font, &resume, &h, &w);
    CreateButton(renderer, font, &replay, &h, &w);
    CreateButton(renderer, font, &save, &h, &w);
    CreateButton(renderer, font, &exit, &h, &w);
    CreateButton(renderer, font, &mainb , &h , &w);
   
    
    
    
    
}



void renderText(SDL_Renderer *renderer, const char *text, TTF_Font *font, SDL_Color color, int x, int y) {
    // Render text to a surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface == NULL) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        return;
    }

    // Convert surface to texture
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Define the destination rectangle for rendering
    SDL_Rect destRect = {x, y, textSurface->w, textSurface->h};

    // Render the texture to the screen
    SDL_RenderCopy(renderer, textTexture, NULL, &destRect);

    // Clean up
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}




void analog(SDL_Renderer* renderer, TTF_Font* font, Button up,Button right, Button down, Button left, int buttonheight , int buttonwidth) {
    int h = buttonheight, w = buttonwidth;
    //SDL_SetRenderDrawColor(renderer, 9, 173, 255, 1); // Semi-transparent black
    //SDL_RenderFillRect(renderer, NULL);
    CreateButton(renderer, font, &up, &h, &w);
    CreateButton(renderer, font, &right, &h, &w);
    CreateButton(renderer, font, &down, &h, &w);
    CreateButton(renderer, font, &left, &h, &w);
    
   
    
    
    
    
}