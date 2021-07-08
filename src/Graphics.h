#pragma once
#include <list>
#include <memory>
#include <vector>

#include "Sprite.h"

class Graphics {
   public:
    Graphics(int windowW, int windowH);
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    Graphics(Graphics&&) = delete;
    Graphics& operator=(Graphics&&) = delete;
    ~Graphics();
    void drawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
    void startDraw();
    void endDraw();
    std::list<Sprite*> loadSprites(std::list<std::string> filenames, bool clear = false);
    void changeTexturepack(int id);

    SDL_Renderer* const getRenderer();
    int getWindowWidth();
    int getWindowHeight();

   private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    int windowWidth;
    int windowHeight;

    std::string texture_pack;
    std::vector<std::unique_ptr<Sprite>> sprites;
};