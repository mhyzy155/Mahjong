#pragma once
#include <SDL2/SDL_ttf.h>

#include "Graphics.h"

class Text {
public:
	Text(std::string txt, int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    Text(std::string txt, int size, SDL_Color col);
    Text(const Text &t);
    ~Text();
    void drawText(int x, int y, SDL_Surface* destination);
    void drawText(int x, int y, SDL_Renderer* renderer);
    SDL_Surface* getTextSurface();
    SDL_Rect getTextRect();

private:
    SDL_Color color;
    int font_size;
    std::string text;
    static size_t count;
};