/*
# Copyright (c) 2024, 2025 
ismail ziad <ziad0040@gmail.com>

*/


#include <SDL2/SDL.h>
#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>



void deplacer_vers_bas(int M[4][4]) {
    for (int k=0;k<4;k++){
    for (int j=0;j<4; j++) {
        for (int i=3;i>0;i--) {
            if (M[i][j]==0) {
                M[i][j]=M[i-1][j];
                M[i-1][j] = 0;
            }
        }
    }
}}
int double_vers_bas(int M[4][4]) {
    int s=0;
    for (int j=0;j<4; j++) {
        for (int i=3;i>0;i--) {
            if (M[i][j] == M[i-1][j]&&M[i][j]!=0) {
                M[i][j]= 2*M[i][j];s=s+M[i][j];
                M[i-1][j] = 0;
            }
        }
    }
    return(s);
}

int en_bas(int M[4][4]) {
    int s;
    deplacer_vers_bas(M);
    s=double_vers_bas(M);
    deplacer_vers_bas(M);
    return(s);
}
int double_vers_haut(int M[4][4]) {
    int s=0;
    for (int j=0;j<4; j++) {
        for (int i=0;i<3;i++) {
            if (M[i][j]==M[i+1][j]&&M[i][j]!= 0) {
                M[i][j]=2*M[i][j];s=s+M[i][j];
                M[i+1][j]=0;
            }
        }
    }
    return(s);
}
void deplacer_vers_haut(int M[4][4]) {
    for (int k=0;k<4;k++){
    for (int j=0;j<4; j++) {
        for (int i=0;i<3;i++) {
            if (M[i][j]==0) {
                M[i][j]=M[i+1][j];
                M[i+1][j] = 0;
            }
        }
    }
}}
int en_haut(int M[4][4]){
int s;
deplacer_vers_haut(M);
s=double_vers_haut(M);
deplacer_vers_haut(M);
return(s);
}

 int double_vers_gauche(int M[4][4]){
    int s=0;
    for (int i=0;i<4; i++) {
        for (int j=0;j<3;j++) {
            if (M[i][j] == M[i][j+1]&&M[i][j] != 0) {
                M[i][j]= 2*M[i][j];s=s+M[i][j];
                M[i][j+1] = 0;
            }
        }
    }
    return(s);
}
void deplacer_vers_gauche(int M[4][4]) {
    for (int k=0;k<4;k++){
    for (int i=0;i<4; i++) {
        for (int j=0;j<3;j++) {
            if (M[i][j] == 0) {
                M[i][j]= M[i][j+1];
                M[i][j+1] = 0;
            }
        }
    }
}}
int a_gauche(int M[4][4]){
int s;
deplacer_vers_gauche(M);
s=double_vers_gauche(M);
deplacer_vers_gauche(M);
return(s);
}
int double_vers_droite(int M[4][4]){
    int s=0;
    for (int i=0;i<4; i++) {
        for (int j=3;j>0;j--) {
            if (M[i][j] == M[i][j-1]&&M[i][j] != 0) {
                M[i][j]= 2*M[i][j];s=s+M[i][j];
                M[i][j-1] = 0;
            }
        }
    }
    return(s);
}
void deplacer_vers_droite(int M[4][4]) {
    for (int k=0;k<4;k++){
    for (int i=0;i<4; i++) {
        for (int j=3;j>0;j--) {
            if (M[i][j]==0) {
                M[i][j]=M[i][j-1];
                M[i][j-1]=0;
            }
        }
    }
}}
a_droite(int M[4][4]){
int s;
deplacer_vers_droite(M);
s=double_vers_droite(M);
deplacer_vers_droite(M);
return(s);
}






