

/*

# Copyright (c) 2024, 2025 rahim abderrahmane <abderrahman.rahim18@gmail.com >

*/




#include "score.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "rounded.h"



#define HIGH_SCORE_FILE "highscore.txt"
#define MAX_SCORE_TEXT_LENGTH 50

// Updates the current score by adding points
void updateScore(Score *score, int points) {
    score->currentScore += points;
    if (score->currentScore > score->highScore) {
        score->highScore = score->currentScore;
        SaveHighScore(score);
    }
}

// Toggles the active state of the score
void toggleScore(Score* score) {
    score->active = !score->active;
}

// Resets the current score
void ResetScore(Score *score) {
    score->currentScore = 0;
}

// Loads the high score from a file
void LoadHighScore(Score *score) {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (file) {
        fscanf(file, "%d", &score->highScore);
        fclose(file);
    } else {
        score->highScore = 0;
    }
}

// Saves the high score to a file
void SaveHighScore(Score *score) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file) {
        fprintf(file, "%d", score->highScore);
        fclose(file);
    }
}


void RenderLeaderboard(SDL_Renderer *renderer, TTF_Font *font, int *leaderboard, int leaderboardSize) {
    SDL_Color white = {255, 255, 255, 255}; // White text color
    SDL_Rect dstRect;
    int yOffset = 50; // Initial y-position for text rendering

    for (int i = 0; i < leaderboardSize; i++) {
        char scoreText[50];
        snprintf(scoreText, sizeof(scoreText), "%d. %d", i + 1, leaderboard[i]);

        SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, white);
        if (!textSurface) {
            printf("Failed to render text: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            printf("Failed to create texture: %s\n", SDL_GetError());
            SDL_FreeSurface(textSurface);
            continue;
        }

        dstRect.x = 100;                // X-position
        dstRect.y = yOffset;            // Y-position
        dstRect.w = textSurface->w;     // Width of text
        dstRect.h = textSurface->h;     // Height of text

        SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        yOffset += 40; // Line spacing
    }
}





void RenderLeaderboardFromFile1(SDL_Renderer* renderer, TTF_Font* font, const char* filename, int screenWidth, int screenHeight) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};  // White color for text
    SDL_Color rectColor = {1, 172, 228, 255};   // Blue color for the rectangle background
    SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);

    char line[256];
    int yPosition = 500;  // Starting y-coordinate for the first score
    int playerNumber = 1; // Player counter for labeling
    int rectWidth = 700;  // Fixed rectangle width
    int rectHeight = 100;  // Fixed rectangle height

    while (fgets(line, sizeof(line), file)) {
        // Trim newline
        line[strcspn(line, "\n")] = '\0';

        // Create a surface for the player label
        char playerLabel[20];
        snprintf(playerLabel, sizeof(playerLabel), "Player %d", playerNumber);
        SDL_Surface* playerSurface = TTF_RenderText_Solid(font, playerLabel, textColor);
        if (!playerSurface) {
            printf("Failed to render player label! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
        int playerWidth = playerSurface->w;
        int playerHeight = playerSurface->h;

        // Create a surface for the score
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, line, textColor);
        if (!scoreSurface) {
            SDL_FreeSurface(playerSurface);
            printf("Failed to render score! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        int scoreWidth = scoreSurface->w;
        int scoreHeight = scoreSurface->h;

        // Center the rectangle horizontally
        int xPosition = (screenWidth - rectWidth) / 2;
        SDL_Rect rect = {xPosition, yPosition, rectWidth, rectHeight};

        // Draw the rectangle background
        int radius = 20;
        fillRoundedRect(renderer, rect, radius);

        // Position the player label on the left (inside padding of 20)
        SDL_Rect playerRect = {xPosition + 20, yPosition + (rectHeight - playerHeight) / 2, playerWidth, playerHeight};
        SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

        // Position the score on the right (inside padding of 20)
        SDL_Rect scoreRect = {xPosition + rectWidth - scoreWidth - 20, yPosition + (rectHeight - scoreHeight) / 2, scoreWidth, scoreHeight};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

        // Clean up surfaces and textures
        SDL_FreeSurface(playerSurface);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(playerTexture);
        SDL_DestroyTexture(scoreTexture);

        // Update positions for the next entry
        yPosition += rectHeight + 20; // Space between rows
        playerNumber++;               // Increment player count
    }

    fclose(file);
}

void RenderLeaderboardFromFile2(SDL_Renderer* renderer, TTF_Font* font, const char* filename, int screenWidth, int screenHeight) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};  // White color for text
    SDL_Color rectColor = {1, 172, 228, 255};   // Blue color for the rectangle background
    SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);

    char line[256];
    int yPosition = 650;  // Starting y-coordinate for the first score
    int playerNumber = 2; // Player counter for labeling
    int rectWidth = 700;  // Fixed rectangle width
    int rectHeight = 100;  // Fixed rectangle height

    while (fgets(line, sizeof(line), file)) {
        // Trim newline
        line[strcspn(line, "\n")] = '\0';

        // Create a surface for the player label
        char playerLabel[20];
        snprintf(playerLabel, sizeof(playerLabel), "Player %d", playerNumber);
        SDL_Surface* playerSurface = TTF_RenderText_Solid(font, playerLabel, textColor);
        if (!playerSurface) {
            printf("Failed to render player label! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
        int playerWidth = playerSurface->w;
        int playerHeight = playerSurface->h;

        // Create a surface for the score
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, line, textColor);
        if (!scoreSurface) {
            SDL_FreeSurface(playerSurface);
            printf("Failed to render score! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        int scoreWidth = scoreSurface->w;
        int scoreHeight = scoreSurface->h;

        // Center the rectangle horizontally
        int xPosition = (screenWidth - rectWidth) / 2;
        SDL_Rect rect = {xPosition, yPosition, rectWidth, rectHeight};

        // Draw the rectangle background
        int radius = 20;
        fillRoundedRect(renderer, rect, radius);

        // Position the player label on the left (inside padding of 20)
        SDL_Rect playerRect = {xPosition + 20, yPosition + (rectHeight - playerHeight) / 2, playerWidth, playerHeight};
        SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

        // Position the score on the right (inside padding of 20)
        SDL_Rect scoreRect = {xPosition + rectWidth - scoreWidth - 20, yPosition + (rectHeight - scoreHeight) / 2, scoreWidth, scoreHeight};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

        // Clean up surfaces and textures
        SDL_FreeSurface(playerSurface);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(playerTexture);
        SDL_DestroyTexture(scoreTexture);

        // Update positions for the next entry
        yPosition += rectHeight + 20; // Space between rows
        playerNumber++;               // Increment player count
    }

    fclose(file);
}

void RenderLeaderboardFromFile3(SDL_Renderer* renderer, TTF_Font* font, const char* filename, int screenWidth, int screenHeight) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};  // White color for text
    SDL_Color rectColor = {1, 172, 228, 255};   // Blue color for the rectangle background
    SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);

    char line[256];
    int yPosition = 800;  // Starting y-coordinate for the first score
    int playerNumber = 3; // Player counter for labeling
    int rectWidth = 700;  // Fixed rectangle width
    int rectHeight = 100;  // Fixed rectangle height

    while (fgets(line, sizeof(line), file)) {
        // Trim newline
        line[strcspn(line, "\n")] = '\0';

        // Create a surface for the player label
        char playerLabel[20];
        snprintf(playerLabel, sizeof(playerLabel), "Player %d", playerNumber);
        SDL_Surface* playerSurface = TTF_RenderText_Solid(font, playerLabel, textColor);
        if (!playerSurface) {
            printf("Failed to render player label! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
        int playerWidth = playerSurface->w;
        int playerHeight = playerSurface->h;

        // Create a surface for the score
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, line, textColor);
        if (!scoreSurface) {
            SDL_FreeSurface(playerSurface);
            printf("Failed to render score! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        int scoreWidth = scoreSurface->w;
        int scoreHeight = scoreSurface->h;

        // Center the rectangle horizontally
        int xPosition = (screenWidth - rectWidth) / 2;
        SDL_Rect rect = {xPosition, yPosition, rectWidth, rectHeight};

        // Draw the rectangle background
        int radius = 20;
        fillRoundedRect(renderer, rect, radius);

        // Position the player label on the left (inside padding of 20)
        SDL_Rect playerRect = {xPosition + 20, yPosition + (rectHeight - playerHeight) / 2, playerWidth, playerHeight};
        SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

        // Position the score on the right (inside padding of 20)
        SDL_Rect scoreRect = {xPosition + rectWidth - scoreWidth - 20, yPosition + (rectHeight - scoreHeight) / 2, scoreWidth, scoreHeight};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

        // Clean up surfaces and textures
        SDL_FreeSurface(playerSurface);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(playerTexture);
        SDL_DestroyTexture(scoreTexture);

        // Update positions for the next entry
        yPosition += rectHeight + 20; // Space between rows
        playerNumber++;               // Increment player count
    }

    fclose(file);
}

void RenderLeaderboardFromFile4(SDL_Renderer* renderer, TTF_Font* font, const char* filename, int screenWidth, int screenHeight) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};  // White color for text
    SDL_Color rectColor = {1, 172, 228, 255};   // Blue color for the rectangle background
    SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);

    char line[256];
    int yPosition = 950;  // Starting y-coordinate for the first score
    int playerNumber = 4; // Player counter for labeling
    int rectWidth = 700;  // Fixed rectangle width
    int rectHeight = 100;  // Fixed rectangle height

    while (fgets(line, sizeof(line), file)) {
        // Trim newline
        line[strcspn(line, "\n")] = '\0';

        // Create a surface for the player label
        char playerLabel[20];
        snprintf(playerLabel, sizeof(playerLabel), "Player %d", playerNumber);
        SDL_Surface* playerSurface = TTF_RenderText_Solid(font, playerLabel, textColor);
        if (!playerSurface) {
            printf("Failed to render player label! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
        int playerWidth = playerSurface->w;
        int playerHeight = playerSurface->h;

        // Create a surface for the score
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, line, textColor);
        if (!scoreSurface) {
            SDL_FreeSurface(playerSurface);
            printf("Failed to render score! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        int scoreWidth = scoreSurface->w;
        int scoreHeight = scoreSurface->h;

        // Center the rectangle horizontally
        int xPosition = (screenWidth - rectWidth) / 2;
        SDL_Rect rect = {xPosition, yPosition, rectWidth, rectHeight};

        // Draw the rectangle background
        int radius = 20;
        fillRoundedRect(renderer, rect, radius);

        // Position the player label on the left (inside padding of 20)
        SDL_Rect playerRect = {xPosition + 20, yPosition + (rectHeight - playerHeight) / 2, playerWidth, playerHeight};
        SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

        // Position the score on the right (inside padding of 20)
        SDL_Rect scoreRect = {xPosition + rectWidth - scoreWidth - 20, yPosition + (rectHeight - scoreHeight) / 2, scoreWidth, scoreHeight};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

        // Clean up surfaces and textures
        SDL_FreeSurface(playerSurface);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(playerTexture);
        SDL_DestroyTexture(scoreTexture);

        // Update positions for the next entry
        yPosition += rectHeight + 20; // Space between rows
        playerNumber++;               // Increment player count
    }

    fclose(file);
}

void RenderLeaderboardFromFile5(SDL_Renderer* renderer, TTF_Font* font, const char* filename, int screenWidth, int screenHeight) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    SDL_Color textColor = {255, 255, 255, 255};  // White color for text
    SDL_Color rectColor = {1, 172, 228, 255};   // Blue color for the rectangle background
    SDL_SetRenderDrawColor(renderer, rectColor.r, rectColor.g, rectColor.b, rectColor.a);

    char line[256];
    int yPosition = 1100;  // Starting y-coordinate for the first score
    int playerNumber = 5; // Player counter for labeling
    int rectWidth = 700;  // Fixed rectangle width
    int rectHeight = 100;  // Fixed rectangle height

    while (fgets(line, sizeof(line), file)) {
        // Trim newline
        line[strcspn(line, "\n")] = '\0';

        // Create a surface for the player label
        char playerLabel[20];
        snprintf(playerLabel, sizeof(playerLabel), "Player %d", playerNumber);
        SDL_Surface* playerSurface = TTF_RenderText_Solid(font, playerLabel, textColor);
        if (!playerSurface) {
            printf("Failed to render player label! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);
        int playerWidth = playerSurface->w;
        int playerHeight = playerSurface->h;

        // Create a surface for the score
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, line, textColor);
        if (!scoreSurface) {
            SDL_FreeSurface(playerSurface);
            printf("Failed to render score! TTF_Error: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        int scoreWidth = scoreSurface->w;
        int scoreHeight = scoreSurface->h;

        // Center the rectangle horizontally
        int xPosition = (screenWidth - rectWidth) / 2;
        SDL_Rect rect = {xPosition, yPosition, rectWidth, rectHeight};

        // Draw the rectangle background
        int radius = 20;
        fillRoundedRect(renderer, rect, radius);

        // Position the player label on the left (inside padding of 20)
        SDL_Rect playerRect = {xPosition + 20, yPosition + (rectHeight - playerHeight) / 2, playerWidth, playerHeight};
        SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

        // Position the score on the right (inside padding of 20)
        SDL_Rect scoreRect = {xPosition + rectWidth - scoreWidth - 20, yPosition + (rectHeight - scoreHeight) / 2, scoreWidth, scoreHeight};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

        // Clean up surfaces and textures
        SDL_FreeSurface(playerSurface);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(playerTexture);
        SDL_DestroyTexture(scoreTexture);

        // Update positions for the next entry
        yPosition += rectHeight + 20; // Space between rows
        playerNumber++;               // Increment player count
    }

    fclose(file);
}

///////


// Function to draw a fully filled rounded rectangle

////////


// Function to render the score and high score
void renderScores(SDL_Renderer *renderer, TTF_Font *font, int score, int highScore, SDL_Rect rect, SDL_Color textColor) {
    // Create strings for the score and high score
    char scoreText[64];
    char highScoreText[64];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    snprintf(highScoreText, sizeof(highScoreText), "High Score: %d", highScore);

    // Create surfaces and textures for the text
    SDL_Surface *scoreSurface = TTF_RenderText_Blended(font, scoreText, textColor);
    SDL_Surface *highScoreSurface = TTF_RenderText_Blended(font, highScoreText, textColor);

    if (!scoreSurface || !highScoreSurface) {
        printf("Text rendering error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Texture *highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);

    if (!scoreTexture || !highScoreTexture) {
        printf("Texture creation error: %s\n", SDL_GetError());
        SDL_FreeSurface(scoreSurface);
        SDL_FreeSurface(highScoreSurface);
        return;
    }

    // Determine positions for the text within the rectangle
    int textSpacing = 10; // Space between score and high score
    SDL_Rect scoreRect = {rect.x + 20, rect.y+10 , scoreSurface->w, scoreSurface->h};
    SDL_Rect highScoreRect = {rect.x + 20, rect.y+10 + scoreSurface->h + textSpacing, highScoreSurface->w, highScoreSurface->h};

    // Render the rectangle background
    SDL_SetRenderDrawColor(renderer, 24, 119, 135, 255); // Black background
    //SDL_RenderFillRect(renderer, &rect);
    int radius = 30; // Corner radius

    fillRoundedRect(renderer, rect, radius);

    // Render the text inside the rectangle
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_RenderCopy(renderer, highScoreTexture, NULL, &highScoreRect);

    // Free resources
    SDL_FreeSurface(scoreSurface);
    SDL_FreeSurface(highScoreSurface);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(highScoreTexture);
}
void renderScoresMACHINE(SDL_Renderer *renderer, TTF_Font *font, int score,  SDL_Rect rect, SDL_Color textColor) {
    // Create strings for the score and high score
    char scoreText[64];
    char highScoreText[64];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);
    

    // Create surfaces and textures for the text
    SDL_Surface *scoreSurface = TTF_RenderText_Blended(font, scoreText, textColor);
    

    if (!scoreSurface ) {
        printf("Text rendering error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    

    if (!scoreTexture ) {
        printf("Texture creation error: %s\n", SDL_GetError());
        SDL_FreeSurface(scoreSurface);
        ;
        return;
    }

    // Determine positions for the text within the rectangle
    int textSpacing = 10; // Space between score and high score
    SDL_Rect scoreRect = {rect.x + 10, rect.y + 10, scoreSurface->w, scoreSurface->h};
    

    // Render the rectangle background
    SDL_SetRenderDrawColor(renderer, 24, 119, 135, 255); // Black background
    //SDL_RenderFillRect(renderer, &rect);
     int radius = 30; // Corner radius

    fillRoundedRect(renderer, rect, radius);

    // Render the text inside the rectangle
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    

    // Free resources
    SDL_FreeSurface(scoreSurface);
    
    SDL_DestroyTexture(scoreTexture);
    
}


#include <stdio.h>
#include <stdlib.h>

#define MAX_SCORES 5  // Limite du nombre de scores

// Fonction pour ajouter un score et trier le fichier
void ajouterEtTrierScore(const char *nomFichier, int nouveauScore) {
    FILE *fichier = fopen(nomFichier, "r+");
    if (fichier == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    int scores[MAX_SCORES];
    int nbrScores = 0;

    // Lecture des scores actuels dans le fichier
    while (fscanf(fichier, "%d", &scores[nbrScores]) == 1 && nbrScores < MAX_SCORES) {
        nbrScores++;
    }

    // Si le fichier contient moins de 5 scores, ajouter le nouveau score
    if (nbrScores < MAX_SCORES) {
        scores[nbrScores] = nouveauScore;
        nbrScores++;
    } else {
        // Si le fichier contient déjà 5 scores, comparer avec le score le plus bas
        int minScoreIndex = 0;
        for (int i = 1; i < MAX_SCORES; i++) {
            if (scores[i] < scores[minScoreIndex]) {
                minScoreIndex = i;
            }
        }

        // Remplacer le plus faible score si le nouveau score est plus élevé
        if (nouveauScore > scores[minScoreIndex]) {
            scores[minScoreIndex] = nouveauScore;
        }
    }

    // Tri des scores en ordre décroissant
    for (int i = 0; i < nbrScores - 1; i++) {
        for (int j = i + 1; j < nbrScores; j++) {
            if (scores[i] < scores[j]) {
                int temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    // Réécrire les scores triés dans le fichier
    rewind(fichier); // Retourne au début du fichier
    for (int i = 0; i < nbrScores; i++) {
        fprintf(fichier, "%d\n", scores[i]);
    }

    // Troncature pour éviter de conserver des scores inutiles
    fflush(fichier);
    fclose(fichier);

    printf("Le score a été ajouté et les scores ont été triés dans le fichier '%s'.\n", nomFichier);
}
int lireHighScore(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    int score = 0;

    if (fichier != NULL) {
        fscanf(fichier, "%d", &score); // Read the score from the file
        fclose(fichier);
    } else {
        perror("Erreur d'ouverture du fichier");
    }

    return score; // Return the score (0 if the file is empty or doesn't exist)
}