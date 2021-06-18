#include "Mouse.h"

void Mouse::getMouseState(int &x, int &y) {
    x = -1;
    y = -1;
    SDL_GetMouseState(&mx, &my);
    x = mx;
    y = my;
}

bool Mouse::isPressed(SDL_Rect rect) {
    SDL_GetMouseState(&mx, &my);
    return (mx >= rect.x && mx < (rect.x + rect.w) && my >= rect.y && my < (rect.y + rect.h)) ? true : false;
}
