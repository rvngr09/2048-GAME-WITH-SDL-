/*

# Copyright (c) 2024, 2025 rahim abderrahmane <abderrahman.rahim18@gmail.com >

*/


#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    int currentScore;
    int highScore;
    bool active; // Added an active state for toggling visibility
} Score;

// Updates the current score by adding points
void updateScore(Score *score, int points);

// Resets the current score
void ResetScore(Score *score);

// Renders the score on the screen at the given position
void RenderScore(SDL_Renderer *renderer, TTF_Font *font, Score *score, SDL_Rect *position);

// Loads and saves high score
void LoadHighScore(Score *score);
void SaveHighScore(Score *score);

// Toggles the active state of the score
void toggleScore(Score *score);
void RenderLeaderboard(SDL_Renderer *renderer, TTF_Font *font, int *leaderboard, int leaderboardSize);
void RenderLeaderboardFromFile(SDL_Renderer *renderer, TTF_Font *font, const char *filePath);
void RenderLeaderboardFromFile1(SDL_Renderer* renderer, TTF_Font* font, const char* filename , int screenWidth, int screenHeight);
void RenderLeaderboardFromFile2(SDL_Renderer* renderer, TTF_Font* font, const char* filename , int screenWidth, int screenHeight);
void RenderLeaderboardFromFile3(SDL_Renderer* renderer, TTF_Font* font, const char* filename , int screenWidth, int screenHeight);
void RenderLeaderboardFromFile4(SDL_Renderer* renderer, TTF_Font* font, const char* filename , int screenWidth, int screenHeight);
void RenderLeaderboardFromFile5(SDL_Renderer* renderer, TTF_Font* font, const char* filename , int screenWidth, int screenHeight);
int lireHighScore(const char *nomFichier);
void renderScores(SDL_Renderer *renderer, TTF_Font *font, int score, int highScore, SDL_Rect rect, SDL_Color textColor) ;
void renderScoresMACHINE(SDL_Renderer *renderer, TTF_Font *font, int score,  SDL_Rect rect, SDL_Color textColor);
#endif
