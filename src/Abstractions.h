#include <SDL2/SDL.h>

class Drawable {
   public:
    virtual void draw(int x, int y, SDL_Renderer* renderer) = 0;
    virtual SDL_Rect getRect() = 0;
};