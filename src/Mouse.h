#pragma once
#include "Graphics.h"
#include "Board.h"

class Mouse {
public:
	void buttonDown(Graphics* gfx, Board* board, int &xindex, int &yindex);
	bool isPressed(SDL_Rect rect);
	
private:	
	int mx, my;
};