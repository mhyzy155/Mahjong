#pragma once
#include <memory>
#include <vector>
#include <list>

#include "Board.h"
#include "Sprite.h"

class Graphics {
   public:
    Graphics(int windowW, int windowH);
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    Graphics(Graphics&&) = delete;
    Graphics& operator=(Graphics&&) = delete;
    ~Graphics();
    void DrawRect(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
    //void DrawBoardSprites(Board* board);
    //void DrawBG();
    void StartDraw();
    //void Draw(Board* board);
    void EndDraw();
    std::list<Sprite*> loadSprites(std::list<std::string> filenames);

    SDL_Renderer* const getRenderer();
    int getWindowWidth();
    int getWindowHeight();

   private:
    void deleteAllTiles();
    void addSprite(Sprite* sprite);         //deprecated
    void addSprite(Sprite* sprite, int n);  //deprecated
    SDL_Renderer* renderer;
    SDL_Window* window;
    int windowWidth;
    int windowHeight;

    std::string texture_pack;
    std::vector<std::unique_ptr<Sprite>> sprites;
};