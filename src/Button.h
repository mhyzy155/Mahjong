#pragma once
#include "Text.h"

class Button : public Drawable {
   public:
    Button(Text* txt, Uint8 r, Uint8 g, Uint8 b, int margin = 0, int w = 0, int h = 0);
    Button(Text* txt, SDL_Color col, int margin = 0, int w = 0, int h = 0);
    Button(const Button&);
    Button(Button&&) = delete;
    Button& operator=(const Button&) = delete;
    Button& operator=(Button&&) = delete;
    ~Button();
    void draw(int x, int y, SDL_Renderer* renderer);
    SDL_Rect getRect();
    void setRect(SDL_Rect rect);

   private:
    Text* button_text;
    SDL_Color button_color;
    SDL_Rect button_rect;
    SDL_Rect text_rect;
};