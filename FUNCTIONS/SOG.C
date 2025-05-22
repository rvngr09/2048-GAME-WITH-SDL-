#include <stdlib.h>
#include <stdio.h>
#include "SOG.h"

// Function ta3 gameover verification 
bool isGameOver(int matrix[SIZE][SIZE]) {
   
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == 0) {
                return false;  // ykmel jeux ymchi
            }
        }
    }

    // verification si y9der ymchi fussioner
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j + 1 < SIZE && matrix[i][j] == matrix[i][j + 1]) {
                return false;  
            }
            if (i + 1 < SIZE && matrix[i][j] == matrix[i + 1][j]) {
                return false;  
            }
        }
    }

    
    return true;
}



// Vérifie ida lha9na 2048
bool isWin(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] >= 2048  ) {
                return true;  
            }
        }
    }
    return false;  
}
