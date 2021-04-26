#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Sprite {
public:
    Sprite(std::string path, SDL_Renderer* renderer);
    ~Sprite();
    void DrawSprite(int x, int y, SDL_Renderer* renderer);
    void DrawSprite(int x, int y, float scale, SDL_Renderer* renderer);
    SDL_Texture* getTex();
    SDL_Rect getRect();

private:
    std::string img_path;
    SDL_Rect img_rect;
    SDL_Texture* texture;
};