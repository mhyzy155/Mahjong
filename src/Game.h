#pragma once
#include "Board.h"
#include "Button.h"
#include "Colors.h"
#include "Graphics.h"
#include "Mouse.h"
#include "Timer.h"
#include "SceneManager.h"

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
    GameState state;
    SceneManager scene_mgr;
    Mouse* mouse;
    Graphics* gfx;
    int windowWidth;
    int windowHeight;
};