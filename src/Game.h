#pragma once
#include "Board.h"
#include "Button.h"
#include "Colors.h"
#include "Graphics.h"
#include "Mouse.h"
#include "Timer.h"

class Game {
public:
    Game();
    ~Game();
    void Update();
    void setStatus(bool status);
    bool getStatus();

    SDL_Window* window;
    SDL_Renderer* renderer;
    Timer* timer;

private:
    void buttonDown();
    bool gameRunning;
    bool gameOriginal;
    int gameScene;
    int gameTileset;
    int gameBoardTiles;
    int tilesets;
    Mouse* mouse;
    Board* board;
    Graphics* gfx;
    int windowWidth;
    int windowHeight;
    int tileXindex;
    int tileYindex;
    std::vector<int> pickedTiles;
    std::vector<Button*> buttonTileset;

    Button* buttonNewgame;
    Button* buttonExit;
    Button* buttonOriginal;
    Button* buttonSimple;
    Button* buttonEasy;
    Button* buttonMedium;
    Button* buttonHard;
    Button* buttonAgain;

    Text* text_tileset;
    Text* text_mode;
    Text* text_difficulty;
    Text* text_win;
};