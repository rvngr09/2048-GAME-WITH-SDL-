/*
# Copyright (c) 2024, 2025 
_________________________________________________________________________________________
|NOM             |PRENOM             |MATRICULE      |EMAIL				                |
|---------------------------------------------------------------------------------------|
|BENALLAL        AMINE               232331666205    benallalamine2209@gmail.com		|
|Noureddine      Hadil Narimane      232331419815    noureddinehadil4@gmail.com		    |
|bassaidouelhadj Rafik               232331530912    rafikbassaidouelhadj@gmail.com	    |
|SENNOUN         Mohamed             232331690602    mohamed.sennoun20@gmail.com		|
|HADIBI          Roumaissa           232331574110    roumaissa.hadibi.dev@gmail.com	    |
|Rahim           Abderrahmane        232331624613    abderrahman.rahim18@gmail.com	    |
|ISMAIL          Ziad                212132055823    iziad0040@gmail.com			    |
|SAADI           Nassim              222233016014    honassim518@gmail.com		        |
|---------------------------------------------------------------------------------------|


*/
#include <windows.h>
#include <unistd.h> 
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <time.h> 
#include "FUNCTIONS/button.h"
#include "FUNCTIONS/clock.h"
#include "FUNCTIONS/matrix.h"
#include <SDL2/SDL_mixer.h>
#include "FUNCTIONS/mouvments.h"
#include "FUNCTIONS/randomiser.h"
#include "FUNCTIONS/machine.h"
#include "FUNCTIONS/score.h"
#include "FUNCTIONS/save.h"
#include  "FUNCTIONS/vsm.h"
#include "FUNCTIONS/background.h"
#include "FUNCTIONS/SOG.h"






int init = SDL_Init(SDL_INIT_EVERYTHING);
int init2 = Mix_Init(0);

int main (int argc, char* args[]) {
    typedef enum{
        running,
        off,
        paused,
        started,
        mainmenu,sp

    }cs;
    
    cs gamestatus;
    typedef enum{
        player,mvsp,mchn,NO,scre
    }cm;
    typedef enum{
       s0,s1,s2
    }ss;
    ss sound;
    cm gamemode;
    ma move;
    gc gametheme=def;
    srand(time(NULL));
    int windowWidth, windowHeight;
    
    bool clockStarted = false;
    SDL_Window* window = NULL;
    SDL_GetWindowSize(window , &windowWidth ,&windowHeight);
    SDL_Renderer* renderer = NULL;
    SDL_Surface* screenSurface = NULL;
    bool showmatrix = false;

    
    // Initialize TTF
    if (TTF_Init() == -1) {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        TTF_Quit();  // Proper cleanup
        return 1;
    }
     // Load font
    int fontsize;
    TTF_Font* paint = TTF_OpenFont("FONTS/SymbolsBySvelocloudy-Regular.ttf", 48);
    TTF_Font* symbols = TTF_OpenFont("FONTS/MaterialIcons-Regular.ttf", 48);
    TTF_Font* symbolsmv = TTF_OpenFont("FONTS/MaterialIcons-Regular.ttf", 200);
    TTF_Font* symbolsmv2 = TTF_OpenFont("FONTS/MaterialIcons-Regular.ttf", 80); // Font size 48
    if (!symbols) {
    printf("Failed to load Material Icons font! TTF_Error: %s\n", TTF_GetError());
    }

    SDL_Color symbolColor = {255, 255, 255, 255}; // White color
    const char* undoSymbol = "\uE166"; 
    printf(undoSymbol);
    TTF_Font* fonttime = TTF_OpenFont("FONTS/Jost-Regular.ttf", 50);
    TTF_Font* font = TTF_OpenFont("FONTS/Jost-Regular.ttf", 35);
    TTF_Font* fontbold = TTF_OpenFont("FONTS/Jost-Bold.ttf" , 35);
    TTF_Font* musi = TTF_OpenFont("FONTS/MUSICELE.ttf" , 35);
    if (!font) {
        SDL_Log("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Get display mode
    //SDL_DisplayMode ecran;
    SDL_DisplayMode ecran;
    
   
    
    if (SDL_GetCurrentDisplayMode(0, &ecran) != 0) {
        printf("Could not get display mode! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        TTF_Quit();
        return 1;
    }
    typedef struct{
        int x,y;
    }cordinates;

    cordinates cord;
   
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    printf("\n\n%dx%d\n\n" , screenHeight,screenWidth);


    
    
    windowWidth = screenWidth-100;
    windowHeight = screenHeight-100;
    
    // Create window
    window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        TTF_Quit();
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
        return 1;
    }


    // Initialize clock
    Clock gameclock;
    InitClock(&gameclock);
    SDL_Texture *texture=NULL;
    SDL_Surface *surface=NULL;
    SDL_Texture *textureintro=NULL;
    SDL_Surface *surfaceintro=NULL;
    SDL_Texture *textureover=NULL;
    SDL_Surface *surfaceover=NULL;
    SDL_Texture *texture2=NULL;
    SDL_Surface *surface2=NULL;
    SDL_Texture *texturetheme=NULL;
    SDL_Surface *surfacetheme=NULL;
    //int thickness = 5;
    SDL_Rect rect = {100, 100, 400, 300}; 
   
    surfaceintro= SDL_LoadBMP("BGS/Frame-7.bmp");
    textureintro= SDL_CreateTextureFromSurface(renderer, surfaceintro);
    SDL_FreeSurface(surfaceintro);
    
   
   

    // Present renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , textureintro,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    surfaceintro= SDL_LoadBMP("BGS/Frame-1.bmp");
    textureintro= SDL_CreateTextureFromSurface(renderer, surfaceintro);
    SDL_FreeSurface(surfaceintro);
    
    
    

    // Present renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , textureintro,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(400);
    surfaceintro= SDL_LoadBMP("BGS/Frame-2.bmp");
    textureintro= SDL_CreateTextureFromSurface(renderer, surfaceintro);
    SDL_FreeSurface(surfaceintro);
    
    
  

    // Present renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , textureintro,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(400);
    surfaceintro= SDL_LoadBMP("BGS/Frame-3.bmp");
    textureintro= SDL_CreateTextureFromSurface(renderer, surfaceintro);
    SDL_FreeSurface(surface);
    
   


    // Present renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , textureintro,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(400);
    
    for (int i = 0; i < 4; i++)
    {
    surfaceintro= SDL_LoadBMP("BGS/Frame-4.bmp");
    textureintro= SDL_CreateTextureFromSurface(renderer, surfaceintro);
    SDL_FreeSurface(surfaceintro);
   
  
    
    // Present renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , textureintro,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(400);
    surfaceintro= SDL_LoadBMP("BGS/Frame-5.bmp");
    textureintro= SDL_CreateTextureFromSurface(renderer, surfaceintro);
    SDL_FreeSurface(surfaceintro);
    
    int thickness=5;
    for (int i = 0; i < thickness; i++) {
        SDL_Rect outline = {rect.x - i, rect.y - i, rect.w + 2 * i, rect.h + 2 * i};
        SDL_RenderDrawRect(renderer, &outline);
    }

    // Present renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , textureintro,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
       
    }
    
    
    







    surface= SDL_LoadBMP("BGS/Frame-7.bmp");
    texture= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    
    surfaceover= SDL_LoadBMP("BGS/Frame-over.bmp");
    textureover= SDL_CreateTextureFromSurface(renderer, surfaceover);
    SDL_FreeSurface(surfaceover);
    surface2= SDL_LoadBMP("BGS/Framehowto.bmp");
    texture2= SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);
    surfacetheme= SDL_LoadBMP("BGS/Framethemes.bmp");
    texturetheme= SDL_CreateTextureFromSurface(renderer, surfacetheme);
    SDL_FreeSurface(surfacetheme);
    

    // Present renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer , texture,NULL,NULL);
    SDL_RenderPresent(renderer);
    //SDL_Delay(3000);
    // Initialize buttons
    int buttonwidth;
    int buttonheight;
    if (screenHeight<=1080 && screenWidth<=1920)
    {
        buttonwidth =(screenWidth / 3)+10;
        buttonheight=(screenHeight / 9);
        cord.x=screenWidth / 2 - buttonwidth / 2;
        cord.y=200;
        int fontsize =30;
        

    }else if (screenHeight==1600 && screenWidth==2560){
      buttonwidth=500;
      buttonheight=100;
        cord.x=1000;
        cord.y=500;
        int fontSize = 40;
        

    }
    
    Button playbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "PLAYER", false , false};
    playbutton.rect.x = cord.x;  
    playbutton.rect.y = cord.y;   
    playbutton.rect.w = buttonwidth ;   
    playbutton.rect.h = buttonheight ;
    playbutton.active = true;
    
    Button machinebutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "MACHINE", false , false};
    machinebutton.rect.x = cord.x;  
    machinebutton.rect.y = playbutton.rect.y + buttonheight+20;//machinebutton.rect.h +10;   
    machinebutton.rect.w = buttonwidth;   
    machinebutton.rect.h = buttonheight;
    machinebutton.active = true;

    Button mvspbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "MACHINE VS PLAYER", false , false};
    mvspbutton.rect.x = cord.x;  
    mvspbutton.rect.y = machinebutton.rect.y +buttonheight +20;   
    mvspbutton.rect.w = buttonwidth;   
    mvspbutton.rect.h = buttonheight;
    mvspbutton.active = true;
    
    Button scorebutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "SCORE", false , false};
    scorebutton.rect.x = cord.x;  
    scorebutton.rect.y = mvspbutton.rect.y +buttonheight +20;   
    scorebutton.rect.w = buttonwidth;   
    scorebutton.rect.h = buttonheight;
    scorebutton.active = true;
    
    Button pausebutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "PAUSE", false , false};
     pausebutton.rect.x = cord.x;  
     pausebutton.rect.y = windowHeight-80;   
     pausebutton.rect.w = buttonwidth-30;   
     pausebutton.rect.h = buttonheight;
     pausebutton.active = true;
    Button resumebutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "RESUME", false , false};
     resumebutton.rect.x = cord.x; 
     resumebutton.rect.y = cord.y;  
     resumebutton.rect.w = buttonwidth;   
     resumebutton.rect.h = buttonheight;
     resumebutton.active = true;
    Button replaybutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "REPLAY", false , false};
    replaybutton.rect.x = cord.x+18;  
    replaybutton.rect.y = resumebutton.rect.y+buttonheight+20;;   
    replaybutton.rect.w = buttonwidth-30;   
    replaybutton.rect.h = buttonheight;
    replaybutton.active = true;
    Button sbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "SAVE", false , false};
    sbutton.rect.x = cord.x;  
    sbutton.rect.y = replaybutton.rect.y + buttonheight+20;   
    sbutton.rect.w = buttonwidth;   
    sbutton.rect.h = buttonheight;
    sbutton.active = true;
    Button Ebutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "EXIT", false , false};
    Ebutton.rect.x = cord.x;  
    Ebutton.rect.y = sbutton.rect.y + buttonheight+20;   
    Ebutton.rect.w = buttonwidth;   
    Ebutton.rect.h = buttonheight;
    Ebutton.active = true;
    Button mainbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "MAIN MENU", false , false};
    mainbutton.rect.x = cord.x;  
    mainbutton.rect.y = Ebutton.rect.y + buttonheight+20;   
    mainbutton.rect.w = buttonwidth;   
    mainbutton.rect.h = buttonheight;
    mainbutton.active = true;
    Button backbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "BACK", false , false};
    backbutton.rect.x = cord.x;  
    backbutton.rect.y = windowHeight-180;   
    backbutton.rect.w = buttonwidth-30;   
    backbutton.rect.h = buttonheight;
    backbutton.active = true;
    Button undobutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "y", false , false};
    undobutton.rect.x = 2200;  
    undobutton.rect.y = 500;   
    undobutton.rect.w = 100;   
    undobutton.rect.h = 100;
    undobutton.active = true;
    Button loadbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "z", false , false};
    loadbutton.rect.x = 2000;  
    loadbutton.rect.y = 500;   
    loadbutton.rect.w = 100;   
    loadbutton.rect.h = 100;
    loadbutton.active = true;
    Button howtobutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "?", false , false};
    howtobutton.rect.x = 150;  
    howtobutton.rect.y = 300;   
    howtobutton.rect.w = 100;   
    howtobutton.rect.h = 100;
    howtobutton.active = true;
    Button themebutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "k", false , false};
    themebutton.rect.x = 150;  
    themebutton.rect.y = 450;   
    themebutton.rect.w = 100;   
    themebutton.rect.h = 100;
    themebutton.active = true;
    Button acbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "H", false , false};
    acbutton.rect.x = 150;  
    acbutton.rect.y = 600;   
    acbutton.rect.w = 100;   
    acbutton.rect.h = 100;
    acbutton.active = true;

    Button darkbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "DARK", false , false};
    darkbutton.rect.x = 1825;  
    darkbutton.rect.y = 1000;   
    darkbutton.rect.w = 100;   
    darkbutton.rect.h = 100;
    darkbutton.active = true;
    Button defaultbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "DEFAULT", false , false};
    defaultbutton.rect.x = 500;  
    defaultbutton.rect.y = 1000;   
    defaultbutton.rect.w = 100;   
    defaultbutton.rect.h = 100;
    defaultbutton.active = true;
    Button cyanbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "CYAN", false , false};
    cyanbutton.rect.x = cord.x+155;  
    cyanbutton.rect.y = 1000;   
    cyanbutton.rect.w = 100;   
    cyanbutton.rect.h = 100;
    cyanbutton.active = true;
    Button upbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "C", false , false};
    upbutton.rect.x = 300;  
    upbutton.rect.y = 600;   
    upbutton.rect.w = 100;   
    upbutton.rect.h = 100;
    upbutton.active = true;
    Button rightbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "A", false , false};
    rightbutton.rect.x = 410; //410 
    rightbutton.rect.y = 730;   
    rightbutton.rect.w = 100;   
    rightbutton.rect.h = 100;
    rightbutton.active = true;
    Button downbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "D", false , false};
    downbutton.rect.x = 300;  
    downbutton.rect.y = 730;   
    downbutton.rect.w = 100;   
    downbutton.rect.h = 100;
    downbutton.active = true;
    Button  leftbutton = {{255, 255, 255, 255}, {9,146,219,64}, {32, 62, 118, 100}, "B", false , false};
    leftbutton.rect.x = 180;  
    leftbutton.rect.y = 730;   
    leftbutton.rect.w = 100;   
    leftbutton.rect.h = 100;
    leftbutton.active = true;
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
    Mix_Music * music = Mix_LoadMUS("audio/themesong.wav");
    Mix_Chunk * psfx = Mix_LoadWAV("audio/pausesfx.wav");
    Mix_Chunk * bsfx = Mix_LoadWAV("audio/buttonsfx.wav");
    
    if(!music){
      printf("Music Error",  Mix_GetError());
    }
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
    printf("Mix_Init failed: %s\n", Mix_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    printf("Mix_OpenAudio failed: %s\n", Mix_GetError());
    }
    Mix_PlayMusic(music,-1);
    Mix_VolumeMusic(4);
    sound=s1;
     int buttonH = undobutton.rect.h;
    int buttonW = undobutton.rect.w;
    
    if (screenHeight<=1080 && screenWidth<=1920)
    {
        pausebutton.rect.y = windowHeight-80; 

    }else if (screenHeight==1600 && screenWidth==2560){
     
        pausebutton.rect.y = windowHeight-200; 

    }
    
    bool machineactive;
    bool ON = true;
    bool isMatrixInitialized = false;
   
    SDL_Event e;
    int score = 0; 
    int undoscore=0; // Initialize score outside the event loop

    // Initialize matrix
    int matrix[4][4] = {
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0}
    };
    int matrixcopy[4][4]={
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0}

    };
    
    int undo1[4][4]={
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0}

    };
    
    int matrixcopymvsp[4][4]={
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0}

    };
    int matrixcopymvsp2[4][4]={
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0}

    };
    
    int matrix1[4][4] = {
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0}
    };
    int matrix2[4][4] = {
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0}
    };
    int matrixcopymchn[4][4]={
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0},
        {0 , 0, 0, 0}
    };
    int gameOverFlag = 0;
    if (randomrvennumber(matrix, &gameOverFlag) == -1) {
    printf("Game Over! No empty tiles available.\n");
    }else{
    printf("Placed a number in the matrix.\n");
    }
    if (randomrvennumber(matrix, &gameOverFlag) == -1) {
    printf("Game Over! No empty tiles available.\n");
    }else{
    printf("Placed a number in the matrix.\n");
    }

    if (randomrvennumber(matrix1, &gameOverFlag) == -1) {
    printf("Game Over! No empty tiles available.\n");
    }else{
    printf("Placed a number in the matrix.\n");
    }
    if (randomrvennumber(matrix1, &gameOverFlag) == -1) {
    printf("Game Over! No empty tiles available.\n");
    }else{
    printf("Placed a number in the matrix.\n");
    }
if (randomrvennumber(matrix2, &gameOverFlag) == -1) {
    printf("Game Over! No empty tiles available.\n");
    }else{
    printf("Placed a number in the matrix.\n");
    }
    if (randomrvennumber(matrix2, &gameOverFlag) == -1) {
    printf("Game Over! No empty tiles available.\n");
    }else{
    printf("Placed a number in the matrix.\n");
    }
    Uint32 lastelapsedtime = 0;
    gamemode=NO;
    bool gameover2;
    while (ON) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                ON = false;
            }

            // Handle button events
            HandleButtonEvent(&e , &playbutton , OnButtonClick);
            HandleButtonEvent(&e , &machinebutton , OnButtonClick);
            HandleButtonEvent(&e , &mvspbutton , OnButtonClick);
            HandleButtonEvent(&e , &scorebutton , OnButtonClick);
            HandleButtonEvent(&e , &sbutton , OnButtonClick);
            HandleButtonEvent(&e , &resumebutton , OnButtonClick);
            HandleButtonEvent(&e , &Ebutton , OnButtonClick);
            HandleButtonEvent(&e , &mainbutton , OnButtonClick);
            HandleButtonEvent(&e , &pausebutton , OnButtonClick);
            HandleButtonEvent(&e , &backbutton , OnButtonClick);
            HandleButtonEvent(&e , &replaybutton , OnButtonClick);
            HandleButtonEvent(&e , &undobutton , OnButtonClick);
            HandleButtonEvent(&e , &loadbutton , OnButtonClick);
            HandleButtonEvent(&e , &howtobutton , OnButtonClick);
            HandleButtonEvent(&e , &themebutton , OnButtonClick);
            HandleButtonEvent(&e , &darkbutton , OnButtonClick);
            HandleButtonEvent(&e , &defaultbutton , OnButtonClick);
            HandleButtonEvent(&e , &cyanbutton , OnButtonClick);
            HandleButtonEvent(&e , &upbutton , OnButtonClick);
            HandleButtonEvent(&e , &rightbutton , OnButtonClick);
            HandleButtonEvent(&e , &leftbutton , OnButtonClick);
            HandleButtonEvent(&e , &downbutton , OnButtonClick);
            HandleButtonEvent(&e , &acbutton , OnButtonClick);

            
            
            
            //gamestatus=running;
            // Handle play button click
            if (gamemode==NO){   
                machinebutton.active=true;
                mvspbutton.active=true;
                playbutton.active=true;
                scorebutton.active=true;
                
                if (howtobutton.isClicked)
                {   
                     SDL_RenderClear(renderer);
    
                    // Set backbutton position for "how to" screen
                    backbutton.rect.x = 1850;  
                    backbutton.rect.y = 135;
                    backbutton.rect.w = buttonwidth;  // Ensure button width is set
                    backbutton.rect.h = buttonheight; // Ensure button height is set
                    backbutton.active=true;
                    // Load and create texture
                    
                    int h=buttonheight;
                    int w=buttonwidth;
                    // Render back button
                    SDL_RenderCopy(renderer , texture2,NULL,NULL);
                    CreateButton(renderer, fontbold, &backbutton, &h, &w);
                    HandleButtonEvent(&e , &backbutton , OnButtonClick);
                    if (backbutton.isClicked)
                    {   Mix_PlayChannel(-1 , bsfx  , 0);
                         howtobutton.isClicked=false;
                        gamestatus=mainmenu;

                    }
                    
                    SDL_RenderPresent(renderer);
                }else{
                    backbutton.rect.x = cord.x;  
                    backbutton.rect.y = windowHeight-180; 
                }
                if (themebutton.isClicked)
                {   SDL_RenderClear(renderer);
                    int h=buttonheight;
                    int w=buttonwidth;
                    
                   

                    

                     // Present renderer
                    
                    SDL_RenderCopy(renderer , texturetheme,NULL,NULL);
                    CreateButton(renderer, fontbold, &defaultbutton, &h, &w);
                    CreateButton(renderer, fontbold, &cyanbutton, &h, &w);
                    CreateButton(renderer, fontbold, &darkbutton, &h, &w);
                    
                    SDL_RenderPresent(renderer);
                    
                }
                
                
                if (playbutton.isClicked) { 
                Mix_PlayChannel(-1 ,  bsfx , 0);
                isMatrixInitialized=false;
                gamestatus=running;
                showmatrix=true;
                playbutton.isClicked = false;
                gamemode=player;
                surface= SDL_LoadBMP("BGS/Frame-6.bmp");
                texture= SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
                
               
                
                 // Present renderer
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer , texture,NULL,NULL);
                SDL_RenderPresent(renderer);
                
                if (!clockStarted) {
                    StartClock(&gameclock);
                    clockStarted = true;
                    initmatrix(matrix);
                    showmatrix = true;
                }else {
                    ResetClock(&gameclock);
                    clockStarted = false;
                }
                
            }else if (replaybutton.isClicked){
                    ResetClock(&gameclock);
                    
            }else if(mvspbutton.isClicked){
                isMatrixInitialized=false;
                gamestatus=running;
                showmatrix=true;
                Mix_PlayChannel(-1 , bsfx  , 0);
                mvspbutton.isClicked = false;
                gamemode=mvsp;
                surface= SDL_LoadBMP("BGS/Frame-6.bmp");
                texture= SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                

                 // Present renderer
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer , texture,NULL,NULL);
                SDL_RenderPresent(renderer);
                
                if (!clockStarted) {
                    StartClock(&gameclock);
                    clockStarted = true;
                    initmatrix(matrix);
                    //showmatrix = true;
                }else {
                    ResetClock(&gameclock);
                    clockStarted = false;
                }
            }else if (scorebutton.isClicked && !showmatrix || gamemode==scre&&!showmatrix) { 
               
                Mix_PlayChannel(-1 , bsfx  , 0);
                SDL_RenderClear(renderer);
                Ebutton.isClicked=false;
                resumebutton.isClicked=false;
                replaybutton.isClicked=false;
                sbutton.isClicked=false;
                pausebutton.active=false;
                //showmatrix=false;
                playbutton.active=false;
                machinebutton.active=false;
                scorebutton.active=false;
                backbutton.active=true;
               
                int h=buttonheight;
                int w=buttonwidth;
               
                SDL_RenderCopy(renderer , texture,NULL,NULL);
                CreateButton(renderer, fontbold, &backbutton , &h , &w); 
                RenderLeaderboardFromFile1(renderer, fontbold, "BDD/1.txt" , screenWidth,screenHeight);
                RenderLeaderboardFromFile2(renderer, fontbold, "BDD/2.txt" , screenWidth,screenHeight);
                RenderLeaderboardFromFile3(renderer, fontbold, "BDD/3.txt" , screenWidth,screenHeight);
                RenderLeaderboardFromFile4(renderer, fontbold, "BDD/4.txt" , screenWidth,screenHeight);
                RenderLeaderboardFromFile5(renderer, fontbold, "BDD/5.txt" , screenWidth,screenHeight);
                HandleButtonEvent(&e, &backbutton, OnButtonClick);
                SDL_RenderPresent(renderer);
                SDL_Delay(30);
                
              
                
                
                
                
                
                
               
                
            }else if(machinebutton.isClicked){
                Mix_PlayChannel(-1 , bsfx  , 0);
                gamemode=mchn;
                isMatrixInitialized=false;
                showmatrix=true;
                machineactive=true;
                printf("....");

            }
            if (backbutton.isClicked)
                {   scorebutton.isClicked=false;
                    Mix_PlayChannel(-1 , bsfx  , 0);
                    playbutton.active=true;
                    machinebutton.active=true;
                    scorebutton.active=true;
                    pausebutton.active=true;
                    mvspbutton.active=true;
                    gamemode=NO;
                    gamestatus=mainmenu;
                    backbutton.isClicked=false;
                    backbutton.active=false;
                    
                }
                if (cyanbutton.isClicked)
            {
                cyanbutton.isClicked=false;
                themebutton.isClicked=false;
                gametheme=cyan;
                printf("theme set to cyan");
            }
            if (darkbutton.isClicked)
            {
                darkbutton.isClicked=false;
                themebutton.isClicked=false;
                gametheme=dark;
                printf("theme set to dark");
            }
            if (defaultbutton.isClicked)
            {
                defaultbutton.isClicked=false;
                themebutton.isClicked=false;
                gametheme=def;
                printf("theme set to default");
            }
            
            }else{
                pausebutton.active=true;
            }
            ////
            
            if (gamemode==player&&undobutton.isClicked)
                 {  Mix_PlayChannel(-1 , bsfx  , 0);
                    undobutton.isClicked=false;
                    printf("undo\n");
                    bool UNDOPOSSIBLE =false;
                    for (int k = 0; k < 4; k++)
                    {
                        for (int n = 0; n < 4; n++)
                            {
                                if (undo1[k][n]!=0)
                                {
                                    UNDOPOSSIBLE =true;
                                    break;
                                }
                                
                            }
                    }
                    
                    if (UNDOPOSSIBLE)
                    {
                    
                    for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                    matrix[i][j] = undo1[i][j];
                        }
                    }
                    score=undoscore;
                    printf("undo completed\n");
                    }
                    
                    
                 }
                    


            /////
           
            if (showmatrix && gamemode==mchn) {
                pausebutton.active=true;
                surface= SDL_LoadBMP("BGS/Frame-6.bmp");
                texture= SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                

                 // Present renderer
                SDL_Color textColor = {255, 255, 255, 255}; // White text
                SDL_Rect rect = {200, 200, 300, 150};
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer , texture,NULL,NULL);
                
                
               
                renderScoresMACHINE(renderer, font, score,  rect, textColor);
                renderMatrix(renderer, matrix, fontbold, windowWidth, windowHeight,gametheme);
                SDL_RenderPresent(renderer);
            } else if(pausebutton.isClicked && !showmatrix&&gamemode==mchn){
            int h = 120, w = 500;
            gamestatus=paused;
            pausebutton.isClicked=false;
            Mix_PlayChannel(-1 , psfx  , 0);
            renderPause(renderer , fontbold,resumebutton, replaybutton,sbutton,mainbutton,Ebutton , buttonheight,buttonwidth);
             
            HandleButtonEvent(&e, &resumebutton, OnButtonClick);
            HandleButtonEvent(&e, &sbutton, OnButtonClick);
            HandleButtonEvent(&e, &mainbutton, OnButtonClick);
            HandleButtonEvent(&e, &Ebutton, OnButtonClick);
            HandleButtonEvent(&e, &replaybutton, OnButtonClick);
            }
            
            bool active=true;
             bool gameover2;
            if (machinebutton.isClicked ) {
                Mix_PlayChannel(-1 , bsfx  , 0);
                pausebutton.active=true;
                //initmatrix(matrix);
                gamemode=mchn;
                machineactive=true;
                gamestatus=running;
                bool gameover;
                while (gameOverFlag != -1   && machineactive && gamemode==mchn){   
                    while(SDL_PollEvent(&e)) { // Poll events inside the loop
                    if (e.type == SDL_QUIT || Ebutton.isClicked==true) {
                     machineactive = false; // Exit the loop properly
                     ON = false;            // Stop the main program loop
                    }else if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if (pausebutton.isClicked) {
                        gamestatus=paused; // Toggle pause state
                    }
                    
                    
                    }
                    }
                    
                    gameover=isGameOver(matrix);
                    if (!gameover)
                    {
                        if (sbutton.isClicked==true)
                    {   init_file_clear("BDD/machinescorefile.txt");
                        save_score(score , "BDD/machinescorefile.txt");
                        Mix_PlayChannel(-1 , bsfx  , 0);
                        sbutton.isClicked=false;
                    }
                    
                    
                    //HandleButtonEvent(&e , &pausebutton , OnButtonClick);
                        bool flip;
                        if (gamemode==mchn && gamestatus!=paused)
                        {   printf("i'm here\n");
                            active=true;
                            
                            score=score+machine(matrix, active , &move);
                        }
                        
                        
                       
                        //int highScore = 5678;
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Clear with white
                //SDL_RenderClear(renderer);
                        
                        /*
                        flip=matrixchange(matrixcopy,matrix);
                        if (matrixchange(matrixcopy,matrix)==false && gamestatus==running)
                        {
                            if (randomrvennumber(matrix, &gameOverFlag) == -1) {
                        printf("Game Over! No empty tiles available.\n");
                        }else{
                         printf("Placed a number in the matrix.\n");
                          }
                            
                        }
                        */
                        
                    
                    
                  
                    
                    
                    
                    if (gamestatus==paused){
                        //machineactive=false;
                        active=false;
                        pausebutton.isClicked=false;
                        gamestatus=paused;
                        machinebutton.isClicked=false;
                        // this was the eror li tkhrgk mn boucle
                        showmatrix=false;
                        ////////////////////////////////////

                    if (gamestatus==paused)
                    {
                    playbutton.active=false;
                    machinebutton.active=false;
                    scorebutton.active=false;
                    
                    resumebutton.active=true;
                    sbutton.active=true;
                    Ebutton.active=true;
                    replaybutton.active=true;
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer , texture ,NULL,NULL);
                    
                    renderPause(renderer, fontbold, resumebutton,replaybutton, sbutton,mainbutton, Ebutton, buttonheight,buttonwidth);
                     //Handle button events for the pause menu
                    HandleButtonEvent(&e, &resumebutton, OnButtonClick);
                    HandleButtonEvent(&e, &sbutton, OnButtonClick);
                    HandleButtonEvent(&e, &Ebutton, OnButtonClick);
                    HandleButtonEvent(&e, &replaybutton, OnButtonClick);
                    HandleButtonEvent(&e, &mainbutton, OnButtonClick);
                    
                    SDL_RenderPresent(renderer); 
                    }
                    if (resumebutton.isClicked)
                    {   Mix_PlayChannel(-1 , bsfx  , 0);
                    active=true;
                    machinebutton.isClicked=true;
                    showmatrix=true;
                    pausebutton.isClicked=false;
                    gamestatus=running;
                    resumebutton.isClicked=false;
                    }else if (Ebutton.isClicked){
                        Mix_PlayChannel(-1 , bsfx  , 0);
                    machineactive=false;
                    gamestatus=off;
                    Ebutton.isClicked=false;
                    ON=false;
                    }else if(mainbutton.isClicked){
                        Mix_PlayChannel(-1 , bsfx  , 0);
                        gamestatus=mainmenu;
                        machineactive=false;
                        score=0;
                        showmatrix=false; 
                        playbutton.active=true;
                        machinebutton.active=true;
                        mvspbutton.active=true;
                        backbutton.active=true;
                        //gamemode=NO;


                    }else if(replaybutton.isClicked){
                        Mix_PlayChannel(-1 , bsfx  , 0);
                        gamemode=mchn;
                        showmatrix=true;
                        machineactive=true;
                            initmatrix(matrix);
                            initmatrix(matrixcopymchn);
                            active=false;
                            replaybutton.isClicked=false;
                            //clockStarted=true;
                            pausebutton.isClicked=false;
                            gamestatus=running;
                            score=0;


                    }
              
                
                } 
                    HandleButtonEvent(&e , &pausebutton , OnButtonClick);
                    if (pausebutton.isClicked)
                    {   
                        gamestatus=paused;
                    }
                    /*
                    if (matrixchange(matrixcopy,matrix1)==false && gamestatus==running){
                    if (randomrvennumber(matrix1, &gameOverFlag) == -1 && machineactive!=false) {
                     printf("Game Over! No empty tiles available.\n");
                    }else{
                    printf("Placed a number in the matrix.\n");
                    }
                    }*/
                    
                    
                    /*if (matrixchange(matrixcopy,matrix)==false && gamestatus==running){
                    if (randomrvennumber(matrix, &gameOverFlag) == -1 && machineactive!=false) {
                     printf("Game Over! No empty tiles available.\n");
                    }else{
                    printf("Placed a number in the matrix.\n");
                    }
                    }*/
                    
                    if (gamestatus==running)
                    {
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer , texture ,NULL,NULL);
                    SDL_Color txtColor = {255, 255, 255, 255}; 

                   
                     switch (move)
                {
                case h:
                        renderText(renderer, "C", symbolsmv, txtColor, 2000, 600);
                    break;
                case b:
                        renderText(renderer, "D", symbolsmv, txtColor, 2000, 600);
                    break;
                case g:
                        renderText(renderer, "B", symbolsmv, txtColor, 2000, 600);
                    break;
                case d:
                        renderText(renderer, "A", symbolsmv, txtColor, 2000, 600);
                    break;
                default:
                    break;
                }
                    renderMatrix(renderer, matrix, font, windowWidth , windowHeight,gametheme); // Render the matrix
                    int bh=buttonheight;
                    int bw=buttonwidth;
                    
                    CreateButton(renderer, fontbold, &pausebutton, &bh, &bw); // render present pause button ffs
                    SDL_RenderPresent(renderer); // Present the updated screen
                    SDL_Delay(1000);
                    
                    }
                    //SDL_SetRenderDrawColor(renderer, 0, 172, 201, 255); // Set background color
                    SDL_RenderClear(renderer);
                    
                   
                    
                       
                    }else{
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer , textureover,NULL,NULL);
                        SDL_RenderPresent(renderer);
                    }
                    
                    
                }
                printf("quite");
            machinebutton.isClicked = false;
                
            }

            bool matrix_ch=false;
            gameover2=isGameOver(matrix);
            if(gamemode==mvsp && showmatrix && !gameover2){  
                playbutton.active=false;
                machinebutton.active=false;
                scorebutton.active=false;
                resumebutton.active=false;
                Ebutton.active=false;
                sbutton.active=false;
                replaybutton.active=false;  
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer , texture ,NULL,NULL);
                
                renderTwoMatrices(renderer ,matrix1,matrix2,fontbold,windowWidth,windowHeight,gametheme);
                
                int h=buttonheight;
                int w=buttonwidth;
                CreateButton(renderer , fontbold , &pausebutton ,&h , &w);
                HandleButtonEvent(&e , &pausebutton , OnButtonClick);
                 SDL_RenderPresent(renderer);
                
               if (pausebutton.isClicked)
                {   
                    Mix_PlayChannel(-1 , psfx  , 0);
                    showmatrix=false;
                    gamestatus=paused;
                
                }
               
                
            }
             
            if (!gameover2)
            {
            if (gamemode==mvsp && showmatrix&&!gameover2 || gamemode==player && showmatrix && !gameover2){   
                
                Ebutton.rect.x = cord.x;  
                Ebutton.rect.y = sbutton.rect.y + buttonheight+20;
                replaybutton.rect.x = cord.x+10;  
                replaybutton.rect.y = resumebutton.rect.y+buttonheight+20;;  
                
                if (e.type == SDL_KEYDOWN && pausebutton.isClicked==false || upbutton.isClicked ||downbutton.isClicked||leftbutton.isClicked|| rightbutton.isClicked  ) {
               printf("Key pressed: %s\n", SDL_GetKeyName(e.key.keysym.sym)); // Debugging key event
               if (pausebutton.isClicked){
                Mix_PlayChannel(-1 , psfx  , 0);
               pausebutton.isClicked=false;
               showmatrix=false;
               clockStarted=false;
               gamestatus=paused;
                }
                
                
                 if (upbutton.isClicked)
                {
                    if(gamemode==mvsp){
                            score+= en_haut(matrix2);
                        }else{
                            for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                        undo1[i][j] = matrix[i][j];
                        }
                        }   
                        undoscore=score;
                        score+= en_haut(matrix);
                        }
                    upbutton.isClicked=false;

                }
                if (downbutton.isClicked)
                {
                    printf("Moving down\n");
                       if (gamemode==mvsp)
                        {
                            score += en_bas(matrix2);
                        }else{for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                        undo1[i][j] = matrix[i][j];
                        }
                        }
                        undoscore=score;
                        score += en_bas(matrix); 

                        }
                    downbutton.isClicked=false;
                }
                if (rightbutton.isClicked)
                {
                    printf("Moving right\n"); // Debugging movement
                        if(gamemode==mvsp){
                            score += a_droite(matrix2);

                        }else{
                            for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                            undo1[i][j] = matrix[i][j];
                             }
                            }
                            undoscore=score;
                            score += a_droite(matrix);
                            
                        }
                    rightbutton.isClicked=false;
                }
                if (leftbutton.isClicked)
                {
                    if (gamemode==mvsp)
                        {
                            score += a_gauche(matrix2);
                        }else{
                        for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                        undo1[i][j] = matrix[i][j];
                        
                        }
                        }
                        undoscore=score;
                        score += a_gauche(matrix);
                        }
                    leftbutton.isClicked=false;
                }
                
                
                
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        if(gamemode==mvsp){
                            score+= en_haut(matrix2);
                        }else{
                            for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                        undo1[i][j] = matrix[i][j];
                        }
                        }   
                        undoscore=score;
                        score+= en_haut(matrix);
                        }
                        
                        
                        break;
                    
                    case SDLK_DOWN:
                       printf("Moving down\n");
                       if (gamemode==mvsp)
                        {
                            score += en_bas(matrix2);
                        }else{for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                        undo1[i][j] = matrix[i][j];
                        }
                        }
                        undoscore=score;
                        score += en_bas(matrix); 

                        } // Debugging movement
                          // Move down
                        
                       
                        break;
                    case SDLK_LEFT:
                        if (gamemode==mvsp)
                        {
                            score += a_gauche(matrix2);
                        }else{
                        for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                        undo1[i][j] = matrix[i][j];
                        
                        }
                        }
                        undoscore=score;
                        score += a_gauche(matrix);
                        } // Move left
                        
                        break;
                    case SDLK_RIGHT:
                        printf("Moving right\n"); // Debugging movement
                        if(gamemode==mvsp){
                            score += a_droite(matrix2);

                        }else{
                            for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                            undo1[i][j] = matrix[i][j];
                             }
                            }
                            undoscore=score;
                            score += a_droite(matrix);
                            
                        }
                         // Move right
                        
                        break;
                    default:
                        break;
                }
                
                
                
           
        
            if (gamemode==player)
            {
                for (int i = 0; i < 4 ; i++) {
            for (int j = 0; j < 4; j++ ) {
            if (matrix[i][j] != matrixcopy[i][j]) {
            matrix_ch = true;
            break;
            }
            }
            }
                
            }
            if (gamemode==mvsp)
            {
                for (int i = 0; i < 4 ; i++) {
            for (int j = 0; j < 4; j++ ) {
            if (matrix2[i][j] != matrixcopymvsp2[i][j]) {
            matrix_ch = true;
            break;
            }
            }
            }
                
            }
            
            
            
       

    if (matrix_ch){
            if(gamemode==mvsp){
                if (randomrvennumber(matrix2, &gameOverFlag) == -1) {
                 printf("Game Over! No empty tiles available.\n");
             }else{
                    printf("Placed a number in the matrix.\n");
                }

            if (randomrvennumber(matrix1, &gameOverFlag) == -1) {
                 printf("Game Over! No empty tiles available.\n");
             }else{
                    printf("Placed a number in the matrix.\n");
                }

            }else{ 
                if (randomrvennumber(matrix, &gameOverFlag) == -1) {
                 printf("Game Over! No empty tiles available.\n");
             }else{
                    printf("Placed a number in the matrix.\n");
                }
            
            }
        }
            
       
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
            matrixcopy[i][j] = matrix[i][j];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
            matrixcopymvsp2[i][j] = matrix2[i][j];
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
            matrixcopymvsp[i][j] = matrix1[i][j];
            }
        }
        }
    }

        
         if (gamemode==mvsp && showmatrix){
                   
                    bool active2=true;
                    machine(matrix1, active2 ,&move);
                    if (randomrvennumber(matrix1, &gameOverFlag) == -1) {
                    printf("Game Over! No empty tiles available.\n");
                    }else{
                    printf("Placed a number in the matrix.\n");
                    }
                
                    
            
            }
        /*
            
            yar7em babkom matochiwch wch dert more les case of and khlo les case of kifkif hakak ik normalement 
            ndir boucle while khiir but bdat ttmhbel mfhmtch 3lah anw mtochiwch ki tzido 3fsa zidoha direct

            
            
            */
            int gameOverFlag = 0;

            }else if (gameover2) {
                showmatrix=false;
             // Clear the renderer
                replaybutton.rect.x=1250;
                Ebutton.rect.x=650;
                replaybutton.rect.y=900;
                Ebutton.rect.y=900;
                replaybutton.active=true;
                Ebutton.active=true;
                pausebutton.active=false;
                // Display Game Over Screen
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer , textureover,NULL,NULL);
                if (gameover2&&Ebutton.isClicked)
                {
                    ajouterScore(score, &gameclock);
                }
                

                
                CreateButton(renderer, fontbold, &replaybutton, &buttonheight, &buttonwidth);
                CreateButton(renderer, fontbold, &Ebutton, &buttonheight, &buttonwidth);

                SDL_RenderPresent(renderer); // Present the updated screen

                // Handle Game Over Buttons
                HandleButtonEvent(&e, &replaybutton, OnButtonClick);
                HandleButtonEvent(&e, &Ebutton, OnButtonClick);

                if (replaybutton.isClicked) {
                    Mix_PlayChannel(-1 , bsfx  , 0);
                    replaybutton.isClicked = false;
                    gamestatus = running; // Reset game status
                    initmatrix(matrix); 
                    gamemode=player;  // Reset the matrix
                    score = 0;            // Reset the score
                    showmatrix = true;
                    gameover2 = false;
                    pausebutton.active=true;    // Clear game-over flag
                } else if (Ebutton.isClicked) {
                    Ebutton.isClicked = false;

                    ON = false;           // Exit the game
                }
            }
            
            
            
    }
        
        
        // Render the matrix if showmatrix is true
        if (showmatrix && gamemode==player && !gameover2) {
            playbutton.active=false;
            machinebutton.active=false;
            scorebutton.active=false;
            resumebutton.active=false;
            Ebutton.active=false;
            sbutton.active=false;
            replaybutton.active=false;

            //pausebutton.active=true;
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer , texture ,NULL,NULL);
                
                SDL_Color color= {255, 255, 255, 255};
                
               
                if (isWin(matrix))
                {   
                    renderText(renderer, "YOU WON !", fontbold, color, 2000, 150);
                    
                }
                
                renderMatrix(renderer, matrix ,fontbold,windowWidth , windowHeight,gametheme);
                renderText(renderer, "UNDO", fontbold, color, 2200, 600);
                renderText(renderer, "LOAD", fontbold, color, 2000, 600);
               
                CreateButton(renderer, symbols, &undobutton, &buttonH, &buttonW);
                CreateButton(renderer, symbols, &loadbutton, &buttonH, &buttonW);
                int h=buttonheight;
                int w=buttonwidth;
                SDL_Color textColor = {255, 255, 255, 255}; // White text
                SDL_Rect rect = {1950, 300, 350, 150};
                int highScore = lireHighScore("BDD/1.txt");
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Clear with white
                //SDL_RenderClear(renderer);
                renderScores(renderer, font, score, highScore, rect, textColor);
                
                CreateButton(renderer , fontbold , &pausebutton ,&h , &w);
                analog(renderer , symbolsmv2,upbutton,rightbutton,downbutton,leftbutton,100,100);
                HandleButtonEvent(&e , &pausebutton , OnButtonClick);
                // Update clock if it's started
                if (clockStarted) {
                updateclock(&gameclock);
                Uint32 elapsed = getelapsedtime(&gameclock);
                displayElapsedTime(renderer, fonttime, elapsed);
                }
                //SDL_RenderPresent(renderer);
                if (pausebutton.isClicked){
                    Mix_PlayChannel(-1 , psfx  , 0);
               pausebutton.isClicked=false;
               showmatrix=false;
               clockStarted=false;
               gamestatus=paused;
                }else if (loadbutton.isClicked)
                {   Mix_PlayChannel(-1 , bsfx  , 0);
                    loadbutton.isClicked=false;
                    LoadMatrixAndScoreFromFile(matrix,&score,"BDD/matrixpoint.txt");
                }
                
        }
        
        if (pausebutton.isClicked  || gamestatus==paused ){
                    
                
                pausebutton.isClicked=false;
                gamestatus=paused;
                playbutton.isClicked=false;
                showmatrix=false;
                
              
                if (gamestatus==paused)
                {
                
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer , texture ,NULL,NULL);
                renderPause(renderer, fontbold, resumebutton, replaybutton,sbutton,mainbutton, Ebutton, buttonheight,buttonwidth);
                SDL_RenderPresent(renderer);
                
                }
                
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer , texture ,NULL,NULL);
                renderPause(renderer, fontbold, resumebutton, replaybutton,sbutton,mainbutton, Ebutton, buttonheight,buttonwidth);
                SDL_RenderPresent(renderer);
                
                
                
                
                ////////////////////////////////////

                if (gamestatus==paused){  
                //printf("|--------|");
                resumebutton.active=true;
                sbutton.active=true;
                Ebutton.active=true;
                replaybutton.active=true;

                replaybutton.isClicked=false;
                resumebutton.isClicked=false;
                Ebutton.isClicked=false;
                sbutton.isClicked=false;
                 //Handle button events for the pause menu
                HandleButtonEvent(&e, &resumebutton, OnButtonClick);
                HandleButtonEvent(&e, &sbutton, OnButtonClick);
                HandleButtonEvent(&e, &Ebutton, OnButtonClick);
                HandleButtonEvent(&e, &replaybutton, OnButtonClick);
                if (resumebutton.isClicked)
                {   
                    clockStarted=true;
                    showmatrix=true;
                    pausebutton.isClicked=false;
                    gamestatus=running;
                    resumebutton.isClicked=false;
                    Mix_PlayChannel(-1 , bsfx  , 0);
                    
                    if (clockStarted) {
                        updateclock(&gameclock);
                        Uint32 elapsed = getelapsedtime(&gameclock);
                        displayElapsedTime(renderer, fonttime, elapsed);
                    }
                }else if (Ebutton.isClicked)
                {   
                Mix_PlayChannel(-1 , bsfx  , 0);
                    gamestatus=off;
                    ajouterScore(score, &gameclock);
                    ON=false;
                }else if(sbutton.isClicked==true){
                    Mix_PlayChannel(-1 , bsfx  , 0);
                        init_file_clear("BDD/matrixpoint.txt");
                        SaveMatrixAndScoreToFile(matrix, score, "BDD/matrixpoint.txt");
                        sbutton.isClicked=false;
                }else if(replaybutton.isClicked){
                    
                    if (gamemode==mvsp)
                    {
                        initmatrix(matrix1);
                        initmatrix(matrix2);
                    }else{
                        initmatrix(matrix);
                        initmatrix(undo1);
                    }
                    Mix_PlayChannel(-1 , bsfx  , 0);
                    showmatrix=true;
                    replaybutton.isClicked=false;
                    resumebutton.isClicked=false;
                    Ebutton.isClicked=false;
                    sbutton.isClicked=false;
                    mainbutton.isClicked=false;
                    gamestatus=running;
                    
                    ResetClock(&gameclock); // Ensure ResetClock function resets the clock values
                    clockStarted = true;    // Set the clockStarted flag
                    score = 0;  
                    score=0;
                    
                    

                }else if(mainbutton.isClicked){
                    Mix_PlayChannel(-1 , bsfx  , 0);
                        gamestatus=mainmenu;
                        isMatrixInitialized=false;
                        gamemode=NO;
                        machineactive=false;
                        score=0;
                        //gamestatus=off;
                        showmatrix=false; 
                        scorebutton.active=true;
                        playbutton.active=true;
                        machinebutton.active=true;
                        mvspbutton.active=true;
                        mainbutton.isClicked=false;
                        //gamemode=NO;

                    }
                ////////////
                SDL_RenderPresent(renderer);
                
                
                }
                
        }
        
            
        if (gamestatus!=paused && !showmatrix&&  !scorebutton.isClicked&&gamemode!=mvsp&&gamemode!=player&&!howtobutton.isClicked &&!themebutton.isClicked || !scorebutton.isClicked&&gamestatus==mainmenu && !mvspbutton.isClicked&&gamestatus!=sp&&!howtobutton.isClicked &&!themebutton.isClicked || !scorebutton.isClicked&&gamemode==NO&&gamestatus!=sp&&!howtobutton.isClicked &&!themebutton.isClicked){
            // Render buttons if matrix isn't shown & score button is not clicked or back to main menu
            SDL_RenderClear(renderer);
           
                        
                        
            if (gamestatus==mainmenu)
            {           
                        if (!isMatrixInitialized)
                        {
                        initmatrix(matrix);
                        initmatrix(matrix1);
                        initmatrix(matrix2);
                        initmatrix(matrixcopymchn);
                        initmatrix(matrixcopy);
                        initmatrix(matrixcopymvsp2);
                        initmatrix(matrixcopymvsp);
                        initmatrix(undo1);
                        isMatrixInitialized=true;
                        }
                        
                        score=0;
                       
                        showmatrix=false; 
                        
                        playbutton.active=true;
                        machinebutton.active=true;
                        mvspbutton.active=true;
                        gamemode=NO;
                        mainbutton.isClicked=false;
            }
            
                if (playbutton.isClicked)
                {   Mix_PlayChannel(-1 , bsfx  , 0);
                    gamemode=player;
                    showmatrix=true;
                    ResetClock(&gameclock);
                }else if (machinebutton.isClicked)
                {   Mix_PlayChannel(-1 , bsfx  , 0);
                    gamemode=mchn;
                    showmatrix=true;
                }else if (mvspbutton.isClicked)
                {   Mix_PlayChannel(-1 , bsfx  , 0);
                    gamemode=mvsp;
                    showmatrix=true;
                }else if (scorebutton.isClicked)
                {  
                    gamemode=scre;
                    showmatrix=false;
                    Ebutton.active=false;
                    sbutton.active=false;
                    machinebutton.active=false;
                    mvspbutton.active=false;
                    //scorebutton.isClicked=false;
                    gamestatus=sp;
                }
                
                
                
            
            
            
            
            HandleButtonEvent(&e , &playbutton , OnButtonClick);
            HandleButtonEvent(&e , &scorebutton , OnButtonClick);
            HandleButtonEvent(&e , &mvspbutton , OnButtonClick);
            HandleButtonEvent(&e , &machinebutton , OnButtonClick);
            int h=buttonheight;
            int w=buttonwidth;
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer , texture ,NULL,NULL);
            pausebutton.active=false;
            CreateButton(renderer, fontbold, &playbutton , &h , &w); 
            CreateButton(renderer , fontbold , &scorebutton ,&h , &w);
            CreateButton(renderer , fontbold , &mvspbutton , &h , &w);
            CreateButton(renderer , fontbold , &machinebutton , &h , &w);
            CreateButton(renderer, fontbold, &howtobutton, &buttonH, &buttonW);
            CreateButton(renderer, paint, &themebutton, &buttonH, &buttonW);
            CreateButton(renderer, musi, &acbutton, &buttonH, &buttonW);
            SDL_Color cf ={255,255,255,255};
            if (sound==s2)
            {
                renderText(renderer, "r", musi, cf, 105, 100);
            }
            if (sound==s1)
            {
                renderText(renderer, "s", musi, cf, 105, 100);
            }
            if (sound==s0)
            {
                renderText(renderer, "0", fontbold, cf, 105, 95);
            }
            
            
                if (acbutton.isClicked&&sound==s2)
                {   
                    Mix_VolumeMusic(0);
                    sound=s0;
                    acbutton.isClicked=false;

                }
                if (acbutton.isClicked&&sound==s1)
                {   
                    Mix_VolumeMusic(10);
                    sound=s2;
                    acbutton.isClicked=false;

                }
                if (acbutton.isClicked&&sound==s0)
                {   
                    Mix_VolumeMusic(4);
                    sound=s1;
                    acbutton.isClicked=false;

                }
            
        }
        // Present the renderer
        SDL_RenderPresent(renderer);
        if (gamestatus==off || Ebutton.isClicked)
    {   
        ON=false;
    }
    }
    
    
    // Cleanup
    TTF_CloseFont(font);
    Mix_FreeChunk(bsfx);
    Mix_FreeChunk(psfx);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}