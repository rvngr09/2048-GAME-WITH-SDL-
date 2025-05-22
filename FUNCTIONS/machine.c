
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include"mouvments.h"
#include"matrix.h"
#include "machine.h"
/*
// Function to copy one matrix to another
void copy_matrix(int src[4][4], int dest[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// Check for possible merges when moving down
int check_merge_down(int board[4][4]) {
    int count = 0;
    for (int col = 0; col < 4; col++) {
        for (int row = 3; row > 0; row--) {
            if (board[row][col] == board[row - 1][col] && board[row][col] != 0) {
                count++;
            }
        }
    }
    return count;
}

// Check for possible merges when moving right
int check_merge_right(int board[4][4]) {
    int count = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 3; col > 0; col--) {
            if (board[row][col] == board[row][col - 1] && board[row][col] != 0) {
                count++;
            }
        }
    }
    return count;
}

// Check for possible merges when moving up
int check_merge_up(int board[4][4]) {
    int count = 0;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 3; row++) {
            if (board[row][col] == board[row + 1][col] && board[row][col] != 0) {
                count++;
            }
        }
    }
    return count;
}

// Check for possible merges when moving left
int check_merge_left(int board[4][4]) {
    int count = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] != 0 && board[row][col] == board[row][col + 1]) {
                count++;
            }
        }
    }
    return count;
}

// Determine the best direction to move
int find_best_move(int board[4][4]) {
    int max_merges = 0, best_direction = -1;

    int right_merges = check_merge_right(board);
    int down_merges = check_merge_down(board);
    int left_merges = check_merge_left(board);
    int up_merges = check_merge_up(board);

    if (right_merges > max_merges) {
        max_merges = right_merges;
        best_direction = 2; // Move right
    }
    if (down_merges > max_merges) {
        max_merges = down_merges;
        best_direction = 3; // Move down
    }
    if (left_merges > max_merges) {
        max_merges = left_merges;
        best_direction = 4; // Move left
    }
    if (up_merges > max_merges) {
        max_merges = up_merges;
        best_direction = 1; // Move up
    }

    // If all directions have equal merges, evaluate simulated results
    if (right_merges == down_merges && down_merges == left_merges && left_merges == up_merges) {
        int temp[4][4];
        int max_score = 0, temp_direction = -1;

        copy_matrix(board, temp);
        if (a_droite(temp) > max_score) {
            max_score = a_droite(temp);
            temp_direction = 2;
        }
        copy_matrix(board, temp);
        if (en_bas(temp) > max_score) {
            max_score = en_bas(temp);
            temp_direction = 3;
        }
        copy_matrix(board, temp);
        if (a_gauche(temp) > max_score) {
            max_score = a_gauche(temp);
            temp_direction = 4;
        }
        copy_matrix(board, temp);
        if (en_haut(temp) > max_score) {
            max_score = en_haut(temp);
            temp_direction = 1;
        }
        best_direction = temp_direction;
    }

    // If no valid direction is found, choose a random direction
    if (best_direction == -1) {
        int directions[4] = {1, 2, 3, 4};
        srand(time(NULL));
        best_direction = directions[rand() % 4];
    }
    return best_direction;
}

// Machine AI for making a move
int machine(int board[4][4], bool active, ma* move) {
    if (active) {
        srand(time(NULL));
        int temp_board[4][4];
        copy_matrix(board, temp_board);

        int direction = find_best_move(temp_board);
        int score = 0;

        switch (direction) {
            case 1:
                score = en_haut(board);
                *move = h;
                printf("Moving up\n");
                break;
            case 2:
                score = a_droite(board);
                *move = d;
                printf("Moving right\n");
                break;
            case 3:
                score = en_bas(board);
                *move = b;
                printf("Moving down\n");
                break;
            case 4:
                score = a_gauche(board);
                *move = g;
                printf("Moving left\n");
                break;
            default:
                break;
        }
        return score;
    }
    return 0;
}
*/

void ajouterNombreAleatoire(int M[4][4]) {
    int indices_cases_vide[16][2]; // Tableau pour stocker les positions des cases vides
    int nbr_cases_vides = 0;

    // Trouver toutes les cases vides
    for (int i=0;i<4; i++) {
        for (int j=0;j<4;j++) {
            if (M[i][j] == 0) {
                indices_cases_vide[nbr_cases_vides][0] = i;
                indices_cases_vide[nbr_cases_vides][1] = j;
                nbr_cases_vides++;
            }
        }
    }


    if (nbr_cases_vides == 0) {
        printf("insersion impossible. \n");
        return;
    }

    // Choisir une case vide au hasard
    int indice_aleatoire = rand() % nbr_cases_vides;
    int ligne_aleatoire = indices_cases_vide[indice_aleatoire][0];
    int Col_aleatoire = indices_cases_vide[indice_aleatoire][1];

    int nombre;

    if (rand() % 10 < 5) {
     nombre = 2;
      }
     else {
    nombre = 4;}

    M[ligne_aleatoire][Col_aleatoire] = nombre;
}

int estDansLeCoin(int Q[4][4]) {
int maxTile = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (Q[i][j] > maxTile) {
                maxTile = Q[i][j];
            }
        }
    }

    if (Q[0][0] == maxTile) {
        return 1; 
    } else {
        return 0; 
    }
}


int matrice_pleine_haut(int M[4][4])
{int k=0;
 for (int j=0;j<4; j++) {
        for (int i=0;i<3;i++) {
            if ((M[i][j]*M[i+1][j]) != 0 && M[i][j] != M[i+1][j]) {
                    k++;

            }
        }
    }return(k);
    }
int matrice_pleine_bas(int M[4][4])
{int k=0;
 for (int j=0;j<4; j++) {
        for (int i=3;i>0;i--) {
            if ((M[i][j]*M[i-1][j]) != 0&&M[i][j] != M[i-1][j]) {
                    k++;

            }
        }
    }
return(k);
}
int matrice_pleine_droite(int M[4][4]){
    int k=0;
    for (int i=0;i<4; i++) {
        for (int j=3;j>0;j--) {
            if ((M[i][j]*M[i][j-1])!= 0&&M[i][j] != M[i][j-1]) {
               k++;
            }
        }
    }
    return(k);
}
int matrice_pleine_gauche(int M[4][4]){
    int k=0;
    for (int i=0;i<4; i++) {
        for (int j=0;j<3;j++) {
            if ((M[i][j]*M[i][j+1]) != 0 && M[i][j] != M[i][j+1]) {
               k++;
            }
        }
    }
    return(k);
}
void matrice_pleine(int M[4][4], bool *active){
    
if(matrice_pleine_haut(M)==12){
    if(matrice_pleine_bas(M)==12){
        if(matrice_pleine_droite(M)==12){
            if(matrice_pleine_gauche(M)==12)
            *active=false;
        }
    }

}
}

void copier_matrice(int source[4][4], int destination[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

int possibilite_double_bas(int Q[4][4]) {
    int a=0;
    for (int j=0;j<4; j++) { int p=0;
        for (int i=3;i>0;i--) {
            if (Q[i][j] == Q[i-1][j]&&Q[i][j]!=0) {
                a++;p++;
            }
        }if(p==2) a--;
    }
    return(a);
}
int possibilite_double_droite(int Q[4][4]){
    int a=0;
    for (int i=0;i<4; i++) { int p=0;
        for (int j=3;j>0;j--) { 
            if (Q[i][j] == Q[i][j-1] && Q[i][j] != 0) {
              a++;p++;
            }
        }if(p==2) a--;
    }
    return(a);
}
int possibilite_double_haut(int Q[4][4]) {
    int a=0;
    for (int j=0;j<4; j++) { int p=0;
        for (int i=0;i<3;i++) { 
            if (Q[i][j] == Q[i+1][j] && Q[i][j] != 0) {
                a++;p++;
            }
        }if(p==2) a--;
    }
    return(a);
}
int possibilite_double_gauche(int Q[4][4]){
    int a=0;
    for (int i=0;i<4; i++) { int p=0;
        for (int j=0;j<3;j++) {
            if (Q[i][j] != 0 && Q[i][j] == Q[i][j+1]) {
              a++; p++;
            }
        }if(p==2) a--;
    }
    return(a);
}


int possibilite_en_haut(int Q[4][4]){
int a;
int tmp[4][4];

copier_matrice(Q,tmp);
deplacer_vers_haut(tmp);
return(possibilite_double_haut(tmp));
}

int possibilite_en_bas(int Q[4][4]){
int a;
int tmp[4][4];

copier_matrice(Q,tmp);
deplacer_vers_bas(tmp);
return(possibilite_double_bas(tmp));
}

int possibilite_a_gauche(int Q[4][4]){
int a;
int tmp[4][4];

copier_matrice(Q,tmp);
deplacer_vers_gauche(tmp);
return(possibilite_double_gauche(tmp));
}

int possibilite_a_droite(int Q[4][4]){
int a;
int tmp[4][4];

copier_matrice(Q,tmp);
deplacer_vers_droite(tmp);
return(possibilite_double_droite(tmp));
}



int possibilite (int Q[4][4]) { 

    int max = 0, direction = -1;
    int tmp[4][4];

    copier_matrice(Q,tmp);
    int droite = possibilite_a_droite(tmp);
    copier_matrice(Q,tmp);
    int bas = possibilite_en_bas(tmp);
    copier_matrice(Q,tmp);
    int gauche = possibilite_a_gauche(tmp);
    copier_matrice(Q,tmp);
    int haut = possibilite_en_haut(tmp);
    
    if (droite = max) {
        max = droite;
        direction = 2;
    }
    if (bas > max) {
        max = bas;
        direction = 3;
    }
    if (gauche > max) {
        max = gauche;
        direction = 4;
    }
    if (haut > max) {
        max = haut;
        direction = 1;
    }

    if (droite == gauche && gauche == bas && bas == haut) {
        int W[4][4],x[4][4],y[4][4],z[4][4],l[4][4],m[4][4],n[4][4],o[4][4];
        copier_matrice(Q,W); 
        copier_matrice(Q,x); 
        copier_matrice(Q,y);  
        copier_matrice(Q,z);  
        int s = 0, temp_direction = -1;

        if (a_droite(W) > s) { 
            copier_matrice(Q,W);
            s = a_droite(W);
            temp_direction = 2;
        }
        if (en_bas(x) > s) {
            copier_matrice(Q,x);
            s = en_bas(x);
            temp_direction = 3;
        }
        if (a_gauche(y) > s) {
            copier_matrice(Q,y);
            s = a_gauche(y);
            temp_direction = 4;
        }
        if (en_haut(z) > s) {
            copier_matrice(Q,z);
            s = en_haut(z);
            temp_direction = 1;
        }
        direction = temp_direction;
    }

    
    

    if (direction == -1) {
        int dir[4] = {1, 2, 3, 4};
        srand(time(NULL));
        return dir[rand() % 4];
    }else

    return direction;
}


int machine(int matrix[4][4], bool active,ma* move){
    if (active) {

        int Q[4][4],T[4][4];
        copier_matrice(matrix, Q);
        copier_matrice(matrix, T);   
        int score=0,o,i,j;
        switch (possibilite(Q)) {
            case 1:
                score = en_haut(matrix);
                printf("Moving up\n"); 
                o=0;
                for(i=0;i<4;i++){
                   for(j=0;j<4;j++){
                     if(T[i][j]==matrix[i][j])o++;
                    }
                } 
                if(o!=16) ajouterNombreAleatoire(matrix);
                *move = h;
                
                break;
            case 2:
                score = a_droite(matrix);
                printf("Moving right\n");
                o=0;
                for(i=0;i<4;i++){
                   for(j=0;j<4;j++){
                     if(T[i][j]==matrix[i][j])o++;
                    }
                } 
                if(o!=16) ajouterNombreAleatoire(matrix);
                *move = d;
                break;
            case 3:
                score = en_bas(matrix);
                printf("Moving down\n");
                o=0;
                for(i=0;i<4;i++){
                   for(j=0;j<4;j++){
                     if(T[i][j]==matrix[i][j])o++;
                    }
                } 
                if(o!=16) ajouterNombreAleatoire(matrix);
                *move = b;
                break;
            case 4:
                score = a_gauche(matrix);
                printf("Moving left\n");
                o=0;
                for(i=0;i<4;i++){
                   for(j=0;j<4;j++){
                     if(T[i][j]==matrix[i][j])o++;
                    }
                } 
                if(o!=16) ajouterNombreAleatoire(matrix);
                *move = g;
                break;
            default:
                break;
         }
        return score;
        
    
        matrice_pleine(matrix,&active);
    }
    
    return 0;
    
}