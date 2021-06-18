#pragma once
#include "Board.h"
#include "Graphics.h"

class Mouse {
   public:
    void getMouseState(int &x, int &y);
    bool isPressed(SDL_Rect rect);

   private:
    int mx, my;
};