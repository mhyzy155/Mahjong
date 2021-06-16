#pragma once
#include "Board.h"
#include "Button.h"
#include "Colors.h"
#include "Graphics.h"
#include "Mouse.h"
#include "SceneManager.h"
#include "Timer.h"

class Game {
   public:
    Game();
    ~Game();
    void Update();
    void setStatus(bool status);
    bool getStatus();

   private:
    Graphics* graphics;
    Mouse* mouse;
    GameState state;
    SceneManager scene_mgr;
    Timer timer;
};