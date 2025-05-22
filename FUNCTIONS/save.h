#ifndef save_but
#define save_but
#include <stdio.h>
#include <stdlib.h>
#include "clock.h"
#include <string.h>
#define MATRIX_SIZE 4
void save_score(int score,  const char *nom_fichier);
void init_file_clear(const char *nom_fichier);
void SaveMatrixAndScoreToFile(int matrix[MATRIX_SIZE][MATRIX_SIZE], int score, const char *filename);
void LoadMatrixAndScoreFromFile(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *score, const char *filename);
void ajouterScoreDansFichier(const char *nomFichier, int score, const char *timeString);
void ecrireScore(const char *nomFichier, int score, const char *timeString);
void lireScores(const char *nomsFichiers[], int scores[], char times[][6], int *count);
int lireScore(const char *nomFichier, char* timeString) ;
void convertToMMSS(Uint32 elapsedticks, char* timeString);
void ajouterScore(int nouveauScore, Clock *clock);
#endif