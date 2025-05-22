#include <stdio.h>
#include <stdlib.h>
#include "save.h"
void save_score(int score, const char *nom_fichier) {
    // Ouvre le fichier en mode ajout sans ecraser
    FILE *fichier = fopen(nom_fichier, "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

   
    fprintf(fichier, "%d\n", score);

   
    fclose(fichier);
    printf("Score (%d) sauvegardé avec succès dans %s.\n", score, nom_fichier);
}

void init_file_clear(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'initialisation du fichier");
        return;
    }
    fclose(fichier);
    printf("Fichier '%s' réinitialisé avec succès (contenu effacé).\n", nom_fichier);
}


void SaveMatrixAndScoreToFile(int matrix[MATRIX_SIZE][MATRIX_SIZE], int score, const char *filename) {
    FILE *file;

    // Open the file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    // Write the score to the file
    fprintf(file, "Score: %d\n", score);

    // Write the matrix to the file
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");  // Newline after each row
    }

    // Close the file
    fclose(file);
    printf("Matrix and score saved successfully to %s\n", filename);
}

void LoadMatrixAndScoreFromFile(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *score, const char *filename) {
    FILE *file;

    // Open the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file for reading.\n");
        return;
    }

    // Read the score from the file
    if (fscanf(file, "Score: %d\n", score) != 1) {
        printf("Error: Could not read the score from the file.\n");
        fclose(file);
        return;
    }

    // Read the matrix from the file
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("Error: File format is incorrect or incomplete.\n");
                fclose(file);
                return;
            }
        }
    }

    // Close the file
    fclose(file);
    printf("Matrix and score loaded successfully from %s\n", filename);
}



#define MAX_FICHIERS 5  // 
#include "clock.h"
#include <string.h>
// Fonction pour lire un score depuis un fichier

void convertToMMSS(Uint32 elapsedTicks, char* timeString) {
    // Convert milliseconds to total seconds
    Uint32 totalSeconds = elapsedTicks / 1000;
    Uint32 minutes = totalSeconds / 60;
    Uint32 seconds = totalSeconds % 60;

    // Format it into MM:SS
    snprintf(timeString, 6, "%02u:%02u", minutes, seconds);
}

// Function to read a score and time from a file
int lireScore(const char *nomFichier, char* timeString) {
    FILE *fichier = fopen(nomFichier, "r");
    int score = 0;
    if (fichier != NULL) {
        fscanf(fichier, "%d %s", &score, timeString);  // Read score and time
        fclose(fichier);
    }
    return score;
}

// Function to read all scores and times from the files into an array
void lireScores(const char *nomsFichiers[], int scores[], char times[][6], int *count) {
    *count = 0;
    for (int i = 0; i < MAX_FICHIERS; i++) {
        char timeString[6] = {0};
        int score = lireScore(nomsFichiers[i], timeString);
        if (score > 0) {
            scores[(*count)] = score;
            strcpy(times[*count], timeString);
            (*count)++;
        }
    }
}

// Function to write a score and time to a file
void ecrireScore(const char *nomFichier, int score, const char *timeString) {
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
        fprintf(fichier, "%d %s", score, timeString); // Write score and time
        fclose(fichier);
    } else {
        perror("Erreur d'écriture dans le fichier");
    }
}

// Function to append a score and time to a file
void ajouterScoreDansFichier(const char *nomFichier, int score, const char *timeString) {
    FILE *fichier = fopen(nomFichier, "a");  // Open in append mode
    if (fichier != NULL) {
        fprintf(fichier, "%d %s\n", score, timeString); // Append score and time
        fclose(fichier);
    } else {
        perror("Erreur d'écriture dans le fichier");
    }
}

// Function to sort the scores in descending order based on the score
void trierScores(int scores[], char times[][6], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[i] < scores[j]) {
                int temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;

                char tempTime[6];
                strcpy(tempTime, times[i]);
                strcpy(times[i], times[j]);
                strcpy(times[j], tempTime);
            }
        }
    }
}

// Function to save the top 5 scores and times back to the files
void ecrireTopScores(const char *nomsFichiers[], int scores[], char times[][6], int count) {
    for (int i = 0; i < MAX_FICHIERS && i < count; i++) {
        ecrireScore(nomsFichiers[i], scores[i], times[i]); // Write both score and time
    }
}

// Function to manage the addition of a new score
void ajouterScore(int nouveauScore, Clock *clock) {
    const char *nomsFichiers[MAX_FICHIERS] = {"1.txt", "2.txt", "3.txt", "4.txt", "5.txt"};
    const char *nomTemp = "temp.txt";

    // Array to store the scores and times
    int scores[MAX_FICHIERS + 1] = {0};  // +1 for the temp score
    char times[MAX_FICHIERS + 1][6] = {0};  // Array to store the times in MM:SS format
    int count = 0;

    // Read all scores and times into the array
    lireScores(nomsFichiers, scores, times, &count);

    // Convert the elapsed time to MM:SS format
    char timeString[6];
    convertToMMSS(clock->elapsedticks, timeString);

    // Append the new score and time to the temporary file
    ajouterScoreDansFichier(nomTemp, nouveauScore, timeString);

    // Read the newly added score from the temporary file
    scores[count] = lireScore(nomTemp, timeString);
    strcpy(times[count], timeString);
    count++;

    // Sort all scores in descending order
    trierScores(scores, times, count);

    // Write the sorted scores and times back to the files
    ecrireTopScores(nomsFichiers, scores, times, count);

    // Clear the intermediate file (remove temp.txt)
    remove(nomTemp);  // Remove the temporary file after use
}