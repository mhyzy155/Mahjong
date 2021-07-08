#include "Button.h"

Button::Button(Text* txt, Uint8 r, Uint8 g, Uint8 b, int margin, int w, int h) : button_text{txt}, button_color{r, g, b, 255} {
    text_rect = button_text->getRect();
    button_rect.w = (text_rect.w > w) ? text_rect.w : w;
    button_rect.h = (text_rect.h > h) ? text_rect.h : h;
    button_rect.w += 2 * margin;
    button_rect.h += 2 * margin;
}

Button::Button(Text* txt, SDL_Color col, int margin, int w, int h) : button_text{txt}, button_color{col} {
    text_rect = button_text->getRect();
    button_rect.w = (text_rect.w > w) ? text_rect.w : w;
    button_rect.h = (text_rect.h > h) ? text_rect.h : h;
    button_rect.w += 2 * margin;
    button_rect.h += 2 * margin;
}

Button::Button(const Button& btn) : button_text{new Text(*(btn.button_text))}, button_color{btn.button_color}, text_rect{btn.text_rect}, button_rect{btn.button_rect} {}

Button::~Button() {
    if (button_text) {
        delete button_text;
        button_text = nullptr;
    }
}

void Button::draw(int x, int y, SDL_Renderer* renderer) {
    button_rect.x = x - button_rect.w / 2;
    button_rect.y = y - button_rect.h / 2;
    SDL_SetRenderDrawColor(renderer, button_color.r, button_color.g, button_color.b, button_color.a);
    SDL_RenderDrawRect(renderer, &button_rect);
    SDL_RenderFillRect(renderer, &button_rect);

    button_text->draw(x - text_rect.w / 2, y - text_rect.h / 2, renderer);
}

SDL_Rect Button::getRect() {
    return button_rect;
}

void Button::setRect(SDL_Rect rect){
    button_rect = rect;
}