#pragma once
#include "Graphics.h"
#include "Board.h"

class Mouse {
public:
	//void buttonDown(Graphics* gfx, Board* board, int &xindex, int &yindex);
	void getMouseState(int &x, int &y);
	bool isPressed(SDL_Rect rect);
	
private:
	int mx, my;
};