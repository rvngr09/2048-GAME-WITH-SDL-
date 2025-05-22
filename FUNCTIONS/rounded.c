#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

void fillCircleQuarter(SDL_Renderer *renderer, int cx, int cy, int radius, int quarter) {
    int x = 0;
    int y = radius;
    int d = 1 - radius;

    while (x <= y) {
        // Fill vertical lines for each quarter of the circle
        if (quarter == 0) { // Top-left
            SDL_RenderDrawLine(renderer, cx - x, cy - y, cx, cy - y);
            SDL_RenderDrawLine(renderer, cx - y, cy - x, cx, cy - x);
        } else if (quarter == 1) { // Top-right
            SDL_RenderDrawLine(renderer, cx, cy - y, cx + x, cy - y);
            SDL_RenderDrawLine(renderer, cx, cy - x, cx + y, cy - x);
        } else if (quarter == 2) { // Bottom-right
            SDL_RenderDrawLine(renderer, cx, cy + y, cx + x, cy + y);
            SDL_RenderDrawLine(renderer, cx, cy + x, cx + y, cy + x);
        } else if (quarter == 3) { // Bottom-left
            SDL_RenderDrawLine(renderer, cx - x, cy + y, cx, cy + y);
            SDL_RenderDrawLine(renderer, cx - y, cy + x, cx, cy + x);
        }

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

// Function to draw a fully filled rounded rectangle
void fillRoundedRect(SDL_Renderer *renderer, SDL_Rect rect, int radius) {
    // Ensure the radius doesn't exceed half the width or height
    if (radius * 2 > rect.w) radius = rect.w / 2;
    if (radius * 2 > rect.h) radius = rect.h / 2;

    // Draw and fill the rounded corners
    fillCircleQuarter(renderer, rect.x + radius, rect.y + radius, radius, 0); // Top-left
    fillCircleQuarter(renderer, rect.x + rect.w - radius - 1, rect.y + radius, radius, 1); // Top-right
    fillCircleQuarter(renderer, rect.x + rect.w - radius - 1, rect.y + rect.h - radius - 1, radius, 2); // Bottom-right
    fillCircleQuarter(renderer, rect.x + radius, rect.y + rect.h - radius - 1, radius, 3); // Bottom-left

    // Fill the top and bottom rectangles (excluding the corners)
    SDL_Rect topRect = {rect.x + radius, rect.y, rect.w - 2 * radius, radius};
    SDL_Rect bottomRect = {rect.x + radius, rect.y + rect.h - radius, rect.w - 2 * radius, radius};
    SDL_RenderFillRect(renderer, &topRect);
    SDL_RenderFillRect(renderer, &bottomRect);

    // Fill the central rectangle
    SDL_Rect centerRect = {rect.x, rect.y + radius, rect.w, rect.h - 2 * radius};
    SDL_RenderFillRect(renderer, &centerRect);
}