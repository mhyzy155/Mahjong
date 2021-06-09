#pragma once

#include "Graphics.h"

class Text {
public:
	Text(std::string txt, int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    Text(std::string txt, int size, SDL_Color col);
    Text(const Text &t);
    ~Text();
    void drawText(int x, int y, SDL_Surface* destination);
    void drawText(int x, int y, SDL_Renderer* renderer);
    SDL_Rect getTextRect();

private:
    void updateSurface();
    SDL_Color color;
    int font_size;
    std::string text;
    SDL_Surface *surface;
    static size_t count;
};