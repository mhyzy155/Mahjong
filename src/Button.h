#pragma once
#include "Text.h"

class Button {
public:
    Button(Text* txt, Uint8 r, Uint8 g, Uint8 b, int margin = 0, int w = 0, int h = 0);
    Button(Text* txt, SDL_Color col, int margin = 0, int w = 0, int h = 0);
    ~Button();
    void drawButton(int x, int y, SDL_Renderer* renderer);
    SDL_Rect getButtonRect();

private:
    Text* button_text;
    SDL_Color button_color;
    SDL_Rect button_rect;
};